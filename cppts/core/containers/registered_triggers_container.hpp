#pragma once

#include <mutex>
#include <unordered_map>
#include <string>
#include "../../func_objects/trigger/trigger_info.hpp"

namespace cppts {

class RegisteredTriggersContainer {
public:
	bool is_exist(const std::string& nm) const;

	bool try_add(TriggerInfo&& tg);

	TriggerInfo get(const std::string& nm);

private:
	std::unordered_map<std::string, TriggerInfo> _triggers;
	mutable std::mutex _triggers_mutex;
};

} // namespace cppts