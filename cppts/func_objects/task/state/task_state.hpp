#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>
#include "../task_types.hpp"
#include "task_state_type.hpp"

namespace cppts {

class TaskState {
public:
	TaskState() = default;

	TaskStateType get_status();

	void set_status(TaskStateType st);

	bool empty() const;

	void add_result(TaskResult result);

	bool try_extract_result(TaskResult& result);

	TaskResult wait_for_result();

private:
	std::condition_variable _result_added;

	std::queue<TaskResult> _results;
	mutable std::mutex _results_mutex;

	std::atomic<TaskStateType> _status = TaskStateType::Waiting;
};

} // namespace cppts