#ifndef CORTEX_COMMON_REPOSITORY_HPP
#define CORTEX_COMMON_REPOSITORY_HPP

#include <vector>
#include <string>
#include "common/types.hpp"
#include "common/fs.hpp"
#include "common/network.hpp"

enum class RepositoryType: u8{
    Local  = 0x01,
    Remote = 0x02
};

enum class RepositoryOperationType{
    Nop = 0,
    Create,
    Delete,
    //Update
};

struct RepositoryOperation{
    RepositoryOperationType Type = RepositoryOperationType::Nop;
    fs::path RelativeFilePath;
};


struct RepositoryState: std::vector<fs::path>{
    friend Packet &operator<<(Packet &packet, const RepositoryState &state);
    
    friend Packet &operator>>(Packet &packet, RepositoryState &state);

    friend std::ostream &operator<<(std::ostream &ostream, const RepositoryState &state);
};

extern std::vector<RepositoryOperation> GetStateTransformations(const RepositoryState &old_state, const RepositoryState &new_state);

struct Repository{
    std::string Name;
    fs::path Path;
    RepositoryState LastState;

    Repository(std::string name, fs::path path):
        Name(std::move(name)),
        Path(std::move(path))
    {}

    Repository(const Repository &) = default;

    Repository(Repository &&) = default;

    Repository &operator=(const Repository &) = default;

    Repository &operator=(Repository &&) = default;

    RepositoryState QueryCurrentState();

    std::vector<RepositoryOperation> UpdateState();
};

struct RepositoriesRegistry{
    std::vector<Repository> Repositories;

    bool OpenRepository(fs::path path, std::string name);

    bool CreateRepository(fs::path path, std::string name);
};

#endif//CORTEX_COMMON_REPOSITORY_HPP