#include "func_objects/task/state/task_state_provider.hpp"

namespace cppts {

template<class TResult>
TaskStateProvider<TResult>::TaskStateProvider(std::shared_ptr<TaskState> state) : _state(state)
{ }

template<class TResult>
TaskStateType TaskStateProvider<TResult>::get_status() const {
	return _state->get_status();
}

template<class TResult>
bool TaskStateProvider<TResult>::try_get_result(std::shared_ptr<TResult>& res) {
	TaskResult wrapped_res;

	if (_state->try_extract_result(wrapped_res)) {
		res = unwrap_result(wrapped_res);
		return true;
	}

	return false;
}

template<class TResult>
std::shared_ptr<TResult> TaskStateProvider<TResult>::get_result() {
	return unwrap_result(
		_state->wait_for_result()
	);
}

template<class TResult>
template<class TDur>
void TaskStateProvider<TResult>::wait_for_state(TaskStateType type, TDur sleep) {
	while (get_status() != type) {
		std::this_thread::sleep_for(sleep);
	}
}

template<class TResult>
std::shared_ptr<TResult> TaskStateProvider<TResult>::unwrap_result(TaskResult res) {
	return std::static_pointer_cast<TResult>(res);
}

} // namespace cppts