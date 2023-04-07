#pragma once

#include "task_state.hpp"

namespace cppts {

template<class TResult>
class TaskStateProvider {
public:
	TaskStateProvider() = delete;
	TaskStateProvider(std::shared_ptr<TaskState> state);

	TaskStateType get_status() const;

	bool try_get_result(std::shared_ptr<TResult>& res);

	std::shared_ptr<TResult> get_result();

	template<class TDur>
	void wait_for_state(TaskStateType type, TDur sleep);

private:
	std::shared_ptr<TResult> unwrap_result(TaskResult res);

private:
	std::shared_ptr<TaskState> _state;
};

} // namespace cppts

#include "task_state_provider_impl.hpp"