#include "func_objects/trigger/conditions/predicate_condition.hpp"

namespace cppts {

PredicateCondition::PredicateCondition(const std::function<bool()>& pred) : _predicate(pred)
{ }

bool PredicateCondition::is_achievable() const {
	return true;
}

bool PredicateCondition::is_met(const TriggerState& state) const {
	return _predicate();
}

void PredicateCondition::handle_repetition() { }

std::unique_ptr<ITriggerCondition> PredicateCondition::clone() const {
	return std::make_unique<PredicateCondition>(_predicate);
}

} // namespace cppts