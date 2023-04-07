#pragma once

#include "core/builders/task_proxy_scheduler_builder.hpp"
#include "core/schedulers/task_proxy_scheduler.hpp"

namespace cppts {

TaskProxySchedulerBuilder& TaskProxySchedulerBuilder::depends_on(std::shared_ptr<TaskSchedulerBase> parent) {
	_parent = parent;

	return *this;
}

std::shared_ptr<TaskProxyScheduler> TaskProxySchedulerBuilder::build() {
	if (!_parent) {
		throw std::invalid_argument("proxy scheduler must depend on the other scheduler");
	}

	auto res = new TaskProxyScheduler(_parent, std::move(_info));

	return std::shared_ptr<TaskProxyScheduler>(res);
}

} // namespace cppts