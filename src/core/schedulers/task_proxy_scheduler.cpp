#include "core/schedulers/task_proxy_scheduler.hpp"

namespace cppts {

TaskProxySchedulerBuilder TaskProxyScheduler::create() {
	return TaskProxySchedulerBuilder();
}

void TaskProxyScheduler::run() {
	TaskSchedulerBase::run();

	TS_LOG(_settings.logger, INFO) << "Proxy TS [ " << _settings.name << " ] was run.";
}

void TaskProxyScheduler::stop() {
	TaskSchedulerBase::stop();

	TS_LOG(_settings.logger, INFO) << "Proxy TS [ " << _settings.name << " ] was stopped.";
}

TaskProxyScheduler::~TaskProxyScheduler() {
	TS_LOG(_settings.logger, INFO) << "Proxy TS [ " << _settings.name << " ] is destroying...";
}

TaskProxyScheduler::TaskProxyScheduler(
	std::shared_ptr<TaskSchedulerBase> parent,
	TaskSchedulerParameters&& settings
) : TaskSchedulerBase(parent, std::move(settings))
{ }

void TaskProxyScheduler::init(
	std::shared_ptr<TaskSchedulerBase> parent,
	TaskSchedulerParameters&& settings
) {
	TaskSchedulerBase::init(parent, std::move(settings));

	TS_LOG(_settings.logger, INFO) << "Proxy TS [ " << _settings.name << " ] was successfully initialized.\n";
}

} // namespace cppts