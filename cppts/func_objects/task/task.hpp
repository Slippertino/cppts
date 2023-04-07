#pragma once

#include "task_types.hpp"
#include "task_execution_context.hpp"

namespace cppts {

class ITask {
public:
	virtual void apply_context(const TaskExecutionContext&) = 0;
	virtual TaskResult execute() = 0;
	virtual void on_success() = 0;
	virtual void on_fail(const std::exception&) = 0;
};

} // namespace cppts