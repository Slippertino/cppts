#pragma once

#include <iostream>
#include <future>
#include "../../func_objects/task/state/task_state.hpp"
#include "../../func_objects/task/task_execution_context.hpp"
#include "../../func_objects/task/task.hpp"

namespace cppts {

class TaskExecuter {
public:
	TaskExecuter() = delete;
	TaskExecuter(
		std::shared_ptr<ITask> task, 
		TaskExecutionPolicy pol
	);

	bool try_process(TaskResult& result);

private:
	void process(TaskResult& result);

private:
	TaskExecutionPolicy _policy;
	std::shared_ptr<ITask> _task;
	std::future<TaskResult> _executable;
};

} // namespace cppts