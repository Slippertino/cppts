#include "core/containers/registered_triggers_container.hpp"

namespace cppts {

bool RegisteredTriggersContainer::is_exist(const std::string& nm) const {
	std::lock_guard<std::mutex> locker(_triggers_mutex);

	return _triggers.find(nm) != _triggers.cend();
}

bool RegisteredTriggersContainer::try_add(TriggerInfo&& tg) {
	std::lock_guard<std::mutex> locker(_triggers_mutex);

	if (_triggers.find(tg.name) != _triggers.cend()) {
		return false;
	}

	_triggers.insert({ tg.name, std::move(tg) });

	return true;
}

TriggerInfo RegisteredTriggersContainer::get(const std::string& nm) {
	std::lock_guard<std::mutex> locker(_triggers_mutex);

	return _triggers.at(nm).clone();
}

} // namespace cppts