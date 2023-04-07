#pragma once

#include <memory>
#include <string>
#include "core/logger/logger.hpp"
#include "task_arguments_container.hpp"

namespace cppts {

struct TaskExecutionContext {
	std::string task_name;
	std::string block_name;
	TaskArgumentsContainer args;
	std::shared_ptr<Logger> logger;
};

} // namespace cppts