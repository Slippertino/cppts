#pragma once

#include "task_scheduler_base_builder.hpp"

namespace cppts {

class TaskSchedulerBuilder final : public TaskSchedulerBaseBuilder<TaskSchedulerBuilder> {
public:
	TaskSchedulerBuilder() = default;

	std::shared_ptr<class TaskScheduler> build();
};

} // namespace cppts