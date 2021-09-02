#include "common/repository.hpp"
#include <cassert>
#include <algorithm>
#include <string>
#include "common/log.hpp"
#include "yaml-cpp/yaml.h"

std::vector<RepositoryOperation> GetStateTransformations(const RepositoryState &old_state, const RepositoryState &new_state){
    std::vector<RepositoryOperation> ops;

    for(const fs::path &path: old_state){
        if(std::find(new_state.begin(), new_state.end(), path) == new_state.end())
            ops.push_back({RepositoryOperationType::Delete, path});
    }

    for(const fs::path &path: new_state){
        if(std::find(old_state.begin(), old_state.end(), path) == old_state.end())
            ops.push_back({RepositoryOperationType::Create, path});
    }

    return ops;
}

RepositoryState Repository::QueryCurrentState()const{
    fs::path path = fs::absolute(Path);

    assert(fs::is_directory(path));

    RepositoryState paths; paths.reserve(16);

    for(const fs::directory_entry &entry: fs::recursive_directory_iterator(path)){
        if(entry.status().type() == fs::file_type::regular_file)
            paths.emplace_back(std::move(fs::relative(entry.path(), path)));
    }

    return paths;
}

std::vector<RepositoryOperation> Repository::UpdateState(){
    RepositoryState current_state = QueryCurrentState();

    std::vector<RepositoryOperation> ops = GetStateTransformations(LastState, current_state);

    LastState = std::move(current_state);

    return ops;
}

Packet &operator<<(Packet &packet, const RepositoryState &state){
    packet << (Uint64)state.size();
    for(const fs::path &entry: state)
        packet << entry.string();
    return packet;
}

Packet &operator>>(Packet &packet, RepositoryState &state){
    Uint64 entries_count = 0;
    packet >> entries_count;

    state.reserve(entries_count);

    for(Uint64 i = 0; i<entries_count; i++){
        std::string filename;
        packet >> filename;
        state.push_back(std::move(filename));
    }

    return packet;
}

std::ostream &operator<<(std::ostream &ostream, const RepositoryState &state){
    ostream << "RepositoryState: " << state.size() << " entries" << std::endl;

    for(const auto &entry: state){
        ostream << entry << std::endl;
    }

    return ostream;
}

bool RepositoriesRegistry::OpenRepository(fs::path path, std::string name){
    if(!fs::exists(path))
        return Error("Can't open '{}' repository\n"
                     "Path {} does not exist", name, path.string());

    auto it = Repositories.emplace(std::move(name), std::move(path));
    it.first->second.UpdateState();

    return true;
}

bool RepositoriesRegistry::IsOpen(const std::string &name)const{
    return Repositories.find(name) != Repositories.end();
}

Repository *RepositoriesRegistry::Get(const std::string &name){
    auto it = Repositories.find(name);

    return (it != Repositories.end() ? &it->second : nullptr);
}

bool RepositoriesConfig::LoadFromNode(YAML::Node config){
    constexpr const char *s_Repositories = "Repositories";
    constexpr const char *s_Name = "Name";
    constexpr const char *s_Path = "Path";

    if(!config)
        return Error("[RepositoriesConfig]: node is null");

    if(config[s_Repositories]){
        if(!config[s_Repositories].IsSequence())
            return Error("[RepositoriesPathStorage]: Repositories should be a yaml sequence");

        for(const auto &repo: config[s_Repositories]){
            if(repo[s_Name]            && repo[s_Path]
            && repo[s_Name].IsScalar() && repo[s_Path].IsScalar()){
                std::string name = repo[s_Name].as<std::string>();
                std::string path = repo[s_Path].as<std::string>();

                emplace(std::move(name), std::move(path));
            }else{
                Println("[RepositoriesPathStorage]: invalid repository entry");
            }
        }
    }
    
    return true;
}

bool DefaultPathConfig::LoadFromNode(YAML::Node config){
    constexpr const char *s_DefaultPath = "DefaultPath";

    if(!config)
        return Error("[DefaultPathConfig]: node is null");

    if(!config[s_DefaultPath])
        return Error("[DefaultPathConfig]: No default path in config");

    DefaultPath = config[s_DefaultPath].as<std::string>();

    return true;
}

RepositoriesPathConfig::RepositoriesPathConfig(const char *filepath){
    YAML::Node config = YAML::LoadFile(filepath);

    if(!config)
        throw Exception("[RepositoriesPathStorage]: Can't load config from '{}'", filepath);

    bool path_config = DefaultPathConfig::LoadFromNode(config);
    bool repos_config = RepositoriesConfig::LoadFromNode(config);

    if(!path_config || !repos_config)
        throw Exception("[RepositoriesPathStorage]: Failed to load parent configs");
}

fs::path RepositoriesPathConfig::GetPath(const std::string &name){
    auto it = find(name);

    return (it != end()) ? it->second : DefaultPath / name;
}