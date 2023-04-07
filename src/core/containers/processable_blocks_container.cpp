#include "core/containers/processable_blocks_container.hpp"

namespace cppts {

ProcessableBlocksContainer::ProcessableBlocksContainer(ProcessableBlocksContainer&& pbc) {
    _blocks.merge(std::move(pbc._blocks));
}

bool ProcessableBlocksContainer::is_exist(const std::string& nm) const {
    std::lock_guard<std::mutex> locker{ _blocks_mutex };

    return _blocks.find(nm) != _blocks.cend();
}

void ProcessableBlocksContainer::add(
    const std::string& nm,
    std::shared_ptr<BlockComposite> block
) {
    std::lock_guard<std::mutex> locker{ _blocks_mutex };

    _blocks.insert({ nm, block });
}

void ProcessableBlocksContainer::erase_disabled() {
    std::lock_guard<std::mutex> locker{ _blocks_mutex };

    for (auto it = _blocks.begin(); it != _blocks.end();) {
        auto& block = it->second;

        if (!block->is_enabled() &&
            !block->is_active()) {
            it = _blocks.erase(it);
        }
        else {
            ++it;
        }
    }
}

} // namespace cppts