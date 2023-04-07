#pragma once

#include "../logger/logger.hpp"
#include "../logger/default_logger.hpp"
#include "func_objects/trigger/trigger_info.hpp"
#include "func_objects/trigger/builders/trigger_builder.hpp"
#include "func_objects/switcher/basic_switcher.hpp"

namespace cppts {

struct TaskSchedulerParameters {
	std::string name = "unknown";

	TriggerInfo default_trigger = TriggerBuilder::create()
		.name("default")
		.repeats_count(1)
		.build();

	std::shared_ptr<Logger> logger = std::make_shared<Logger>(
		std::make_shared<DefaultLogger>()
	);

	std::shared_ptr<ISwitcher> switcher = std::make_shared<BasicSwitcher>();
};

} // namespace cppts