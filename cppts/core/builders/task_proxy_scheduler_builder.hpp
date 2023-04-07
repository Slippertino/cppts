#pragma once

#include "task_scheduler_base_builder.hpp"

namespace cppts {

class TaskProxySchedulerBuilder final : public TaskSchedulerBaseBuilder<TaskProxySchedulerBuilder>{
public:
	TaskProxySchedulerBuilder() = default;

	TaskProxySchedulerBuilder& depends_on(std::shared_ptr<class TaskSchedulerBase> parent);

	std::shared_ptr<class TaskProxyScheduler> build();

private:
	std::shared_ptr<class TaskSchedulerBase> _parent = nullptr;
};

} // namespace cppts