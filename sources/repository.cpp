#include "common/repository.hpp"
#include <cassert>
#include <algorithm>

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

RepositoryState Repository::QueryCurrentState(){
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
        state.push_back(filename);
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