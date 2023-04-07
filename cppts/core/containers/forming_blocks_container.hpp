#pragma once

#include <mutex>
#include <unordered_map>
#include <string>
#include "func_objects/task/task_info.hpp"
#include "../units/task_leaf.hpp"
#include "../units/block_composite.hpp"
#include "../../func_objects/trigger/trigger.hpp"

namespace cppts {

class FormingBlocksContainer {
public:
	struct BlockInfo {
		std::shared_ptr<BlockComposite> block;
		std::unordered_map<std::string, std::shared_ptr<void>> tasks_states;
	};

public:
	bool is_exist(const std::string& block_name) const;

	std::string add_block(TriggerInfo&& tg, const std::function<std::string()> block_name_gen);

	bool try_add_task(const std::string& block_name, TaskInfo&& task);

	BlockInfo get(const std::string& block_name);

    void erase(const std::string& block_name);

private:
	std::unordered_map<std::string, BlockInfo> _forming_blocks;
	mutable std::mutex _forming_blocks_mutex;
};

} // namespace cppts
