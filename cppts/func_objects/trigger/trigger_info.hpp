#pragma once

#include <string>
#include <vector>
#include <memory>
#include "trigger_condition.hpp"

namespace cppts {

struct TriggerInfo {
	std::string name;
	std::vector<std::unique_ptr<ITriggerCondition>> conditions;

	TriggerInfo clone() const;
};

} // namespace cppts