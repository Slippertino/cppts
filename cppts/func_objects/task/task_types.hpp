#pragma once

#include <future>
#include <memory>

namespace cppts {

struct TaskEmptyResult { };

using TaskResult = std::shared_ptr<void>;

enum TaskExecutionPolicy {
	AUTO  = std::launch::async | std::launch::deferred,
	SYNC  = std::launch::deferred,
	ASYNC = std::launch::async
};

} // namespace cppts