#pragma once

#include "../builders/task_proxy_scheduler_builder.hpp"
#include "task_scheduler_base.hpp"

namespace cppts {

class TaskProxyScheduler final : public TaskSchedulerBase {
	
	friend class TaskProxySchedulerBuilder;

public:
	static TaskProxySchedulerBuilder create();

	void run() override final;
	void stop() override final;

	~TaskProxyScheduler();

private:
	TaskProxyScheduler() = delete;
	TaskProxyScheduler(
		std::shared_ptr<TaskSchedulerBase> parent,
		TaskSchedulerParameters&& settings
	);

	void init(
		std::shared_ptr<TaskSchedulerBase> parent,
		TaskSchedulerParameters&& settings
	) override final;
};

} // namespace cppts