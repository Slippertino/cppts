#include "func_objects/trigger/trigger_state.hpp"

namespace cppts {

TriggerState::TriggerState(const std::string& name) :
	_name{ name },
	_status{ TriggerStatusType::Waiting }
{ }

TriggerStatusType TriggerState::get_status() const {
	return _status;
}

std::chrono::steady_clock::time_point TriggerState::get_countdown() const {
	return _countdown;
}

std::string TriggerState::get_name() const {
	return _name;
}

void TriggerState::set_status(TriggerStatusType st) {
	_status = st;
}

void TriggerState::reset() {
	_countdown = std::chrono::steady_clock::now();
	_status = TriggerStatusType::Started;
}

} // namespace cppts