#include "func_objects/trigger/conditions/dependency_condition.hpp"

namespace cppts {

DependencyCondition::DependencyCondition(std::shared_ptr<ISwitcherStateProvider> base) : _base(base)
{ }

bool DependencyCondition::is_achievable() const {
	auto is = _base->is_enabled();

	return _base
		? _base->is_enabled()
		: true;
}

bool DependencyCondition::is_met(const TriggerState& state) const {
	return _base
		? _base->is_turned_on()
		: true;
}

void DependencyCondition::handle_repetition() { }

std::unique_ptr<ITriggerCondition> DependencyCondition::clone() const {
	return std::make_unique<DependencyCondition>(_base);
}

} // namespace cppts