#pragma once

#include <iostream>
#include <mutex>
#include <unordered_map>
#include <string>
#include "../schedulers/names_formatter.hpp"
#include "../units/task_leaf.hpp"
#include "../units/block_composite.hpp"
#include "../../func_objects/trigger/trigger.hpp"

namespace cppts {

class ProcessableBlocksContainer {
public:
    ProcessableBlocksContainer() = default;
    ProcessableBlocksContainer(ProcessableBlocksContainer&& pbc);

    bool is_exist(const std::string& nm) const;

    void add(
        const std::string& nm,
        std::shared_ptr<BlockComposite> block
    );

    void erase_disabled();

private:
    std::unordered_map<std::string, std::shared_ptr<BlockComposite>> _blocks = {};
    mutable std::mutex _blocks_mutex;
};

} // namespace cppts