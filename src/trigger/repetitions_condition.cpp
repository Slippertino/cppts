#include "func_objects/trigger/conditions/repetitions_condition.hpp"

namespace cppts {

RepetitionsCondition::RepetitionsCondition(size_t reps_count, bool is_forever) :
	_rest_repetitions_count(reps_count),
	_is_forever(is_forever)
{ }

bool RepetitionsCondition::is_achievable() const {
	return _is_forever || _rest_repetitions_count > 0;
}

bool RepetitionsCondition::is_met(const TriggerState& state) const {
	return _is_forever
		? true
		: _rest_repetitions_count != 0;
}

void RepetitionsCondition::handle_repetition() {
	if (_is_forever) {
		return;
	}

	if (_rest_repetitions_count == 0) {
		throw std::runtime_error("available repetitions count value cannot be less than 0");
	}

	--_rest_repetitions_count;
}

std::unique_ptr<ITriggerCondition> RepetitionsCondition::clone() const {
	return std::make_unique<RepetitionsCondition>(_rest_repetitions_count, _is_forever);
}

} //namespace cppts