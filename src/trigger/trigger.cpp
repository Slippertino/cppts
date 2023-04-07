#include "func_objects/trigger/trigger.hpp"

namespace cppts {

Trigger::Trigger(TriggerInfo&& info) :
	_conditions(std::move(info.conditions)),
	_state(info.name)
{ }

std::string Trigger::get_name() const {
	return _state.get_name();
}

TriggerStatusType Trigger::get_status() const {
	return _state.get_status();
}

bool Trigger::is_ready() const {
	auto st = _state.get_status();

	return
		st == TriggerStatusType::Waiting ||
		st == TriggerStatusType::Ready;
}

void Trigger::start() {
	if (!is_ready()) {
		throw std::runtime_error("impossible to start countdown due to unready trigger stage");
	}

	_state.reset();
}

void Trigger::update() {
	auto st = _state.get_status();

	if (st != TriggerStatusType::Disabled &&
		!is_valid()) {
		_state.set_status(TriggerStatusType::Disabled);
		return;
	}

	if (st != TriggerStatusType::Started) {
		return;
	}

	if (conditions_met()) {
		_state.set_status(TriggerStatusType::Ready);

		for (auto& cond : _conditions) {
			cond->handle_repetition();
		}
	}
}

bool Trigger::is_valid() const {
	for (auto& cond : _conditions) {
		if (!cond->is_achievable()) {
			return false;
		}
	}

	return true;
}

bool Trigger::conditions_met() const {
	for (auto& cond : _conditions) {
		if (!cond->is_met(_state)) {
			return false;
		}
	}

	return true;
}

} // namespace cppts