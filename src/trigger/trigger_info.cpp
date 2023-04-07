#include "func_objects/trigger/trigger_info.hpp"

namespace cppts {

TriggerInfo TriggerInfo::clone() const {
	TriggerInfo res;

	res.name = name;

	for (auto& cond : conditions) {
		res.conditions.push_back(cond->clone());
	}

	return std::move(res);
}

} // namespace cppts