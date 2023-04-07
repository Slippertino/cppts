#include "core/units/task_executer.hpp"

namespace cppts {

TaskExecuter::TaskExecuter(
	std::shared_ptr<ITask> task,
	TaskExecutionPolicy pol
) :
	_policy(pol),
	_task(task),
	_executable(std::async(static_cast<std::launch>(pol), &ITask::execute, task.get()))
{ }

bool TaskExecuter::try_process(TaskResult& result) {
	switch (_policy) {
	case AUTO:
	case SYNC:
		process(result);
		return true;

	case ASYNC:
		if (_executable.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
			process(result);
			return true;
		}
		__fallthrough;

	default:
		return false;
	}
}

void TaskExecuter::process(TaskResult& result) {
	bool failed = false;

	try {
		result = _executable.get();
	}
	catch (const std::exception& ex) {
		failed = true;
		_task->on_fail(ex);
	}

	if (!failed) {
		_task->on_success();
	}
}

} // namespace cppts