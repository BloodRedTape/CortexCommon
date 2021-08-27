#ifndef CORTEX_COMMON_REPOSITORY_HPP
#define CORTEX_COMMON_REPOSITORY_HPP

#include <vector>
#include <string>
#include "common/types.hpp"
#include "common/fs.hpp"

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

using RepositoryState = std::vector<fs::path>;

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

#endif//CORTEX_COMMON_REPOSITORY_HPP