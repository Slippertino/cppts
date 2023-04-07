#pragma once

#include "core/builders/task_scheduler_builder.hpp"
#include "core/schedulers/task_scheduler.hpp"

namespace cppts {

std::shared_ptr<TaskScheduler> TaskSchedulerBuilder::build() {
	auto ptr = new TaskScheduler();
	auto res = std::shared_ptr<TaskScheduler>(ptr);

	res->init(
		res,
		std::move(_info)
	);

	return res;
}

} // namespace cppts