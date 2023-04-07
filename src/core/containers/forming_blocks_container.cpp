#include "core/containers/forming_blocks_container.hpp"

namespace cppts {

bool FormingBlocksContainer::is_exist(const std::string& block_name) const {
	return _forming_blocks.find(block_name) != _forming_blocks.cend();
}

std::string FormingBlocksContainer::add_block(TriggerInfo&& tg, const std::function<std::string()> block_name_gen) {
	std::lock_guard<std::mutex> locker{ _forming_blocks_mutex };

	auto block_name = block_name_gen();

	_forming_blocks.insert({
		block_name,
		BlockInfo {
			std::make_shared<BlockComposite>(std::move(tg)),
			{ }
		}
	});

	return block_name;
}

bool FormingBlocksContainer::try_add_task(const std::string& block_name, TaskInfo&& task) {
	std::lock_guard<std::mutex> locker{ _forming_blocks_mutex };

	auto& info = _forming_blocks.at(block_name);

	if (info.tasks_states.find(task.name) != info.tasks_states.end()) {
		return false;
	}

	auto task_state = std::make_shared<TaskState>();

	task.image->apply_context(
		TaskExecutionContext{
			task.name,
			block_name,
			task.args,
			task.logger
		}
	);

	auto handler = std::make_shared<TaskLeaf>(
		task.policy,
		task.max_pool_size,
		task.image,
		task_state
	);

	info.block->add_task_handler(handler);
	info.tasks_states.insert({ task.name, task_state });

	return true;
}

FormingBlocksContainer::BlockInfo FormingBlocksContainer::get(const std::string& block_name) {
	std::lock_guard<std::mutex> locker{ _forming_blocks_mutex };

	return _forming_blocks.at(block_name);
}

void FormingBlocksContainer::erase(const std::string& block_name) {
	std::lock_guard<std::mutex> locker{ _forming_blocks_mutex };
    
    _forming_blocks.erase(block_name);
}

} // namespace cppts
