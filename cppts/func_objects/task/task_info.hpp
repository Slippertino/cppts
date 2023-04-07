#pragma once

#include "task.hpp"
#include "core/logger/logger.hpp"
#include "task_arguments_container.hpp"
#include "state/task_state.hpp"

namespace cppts {

struct TaskInfo {
	std::string name;
	std::shared_ptr<ITask> image = nullptr;
	std::shared_ptr<Logger> logger = nullptr;
	TaskArgumentsContainer args;
	TaskExecutionPolicy policy = ASYNC;
	size_t max_pool_size = 1;
};

} // namespace cppts