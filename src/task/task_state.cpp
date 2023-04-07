#include "func_objects/task/state/task_state.hpp"

namespace cppts {

TaskStateType TaskState::get_status() {
	return _status;
}

void TaskState::set_status(TaskStateType st) {
	_status = st;
}

bool TaskState::empty() const {
	std::lock_guard<std::mutex> locker(_results_mutex);

	return _results.empty();
}

void TaskState::add_result(TaskResult result) {
	_results_mutex.lock();

	auto valid = std::static_pointer_cast<TaskEmptyResult>(result) != nullptr;

	if (valid) {
		_results.push(result);
	}

	_results_mutex.unlock();

	if (valid) {
		_result_added.notify_one();
	}
}

bool TaskState::try_extract_result(TaskResult& result) {
	std::lock_guard<std::mutex> locker(_results_mutex);

	if (_results.empty()) {
		return false;
	}

	result = _results.front();
	_results.pop();

	return true;
}

TaskResult TaskState::wait_for_result() {
	std::unique_lock<std::mutex> locker(_results_mutex);
	_result_added.wait(locker, [&] { return !_results.empty(); });

	auto result = _results.front();
	_results.pop();

	return result;
}

} // namespace cppts