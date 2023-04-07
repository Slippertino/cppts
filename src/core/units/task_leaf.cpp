#include "core/units/task_leaf.hpp"

namespace cppts {

TaskLeaf::TaskLeaf(
	TaskExecutionPolicy policy,
	size_t max_pool_sz,
	std::shared_ptr<ITask> task,
	std::shared_ptr<TaskState> state
) :
	_policy(policy),
	_max_pool_size(max_pool_sz),
	_task(task),
	_state(state)
{ }

bool TaskLeaf::is_active() const {
	return _state->get_status() == TaskStateType::Active;
}

bool TaskLeaf::is_full() const {
	return _executers.size() == _max_pool_size;
}

void TaskLeaf::start() {
	std::lock_guard<std::mutex> locker(_executers_mutex);

	if (_executers.empty()) {
		_state->set_status(TaskStateType::Active);
	}

	if (_executers.size() < _max_pool_size) {
		_executers.emplace_back(_task, _policy);
	}
}

TaskLeaf::~TaskLeaf() {
	_state->set_status(TaskStateType::Detached);
}

void TaskLeaf::process_base() {
	if (_state->get_status() != TaskStateType::Active) {
		return;
	}

	std::lock_guard<std::mutex> locker(_executers_mutex);
	for (auto it = _executers.begin(); it != _executers.end();) {
		TaskResult result;

		if (it->try_process(result)) {
			_state->add_result(result);
			it = _executers.erase(it);
		}
		else {
			++it;
		}
	}

	if (_executers.empty()) {
		_state->set_status(TaskStateType::Waiting);
	}
}

} // namespace cppts