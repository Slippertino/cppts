#include "func_objects/trigger/conditions/periodicity_condition.hpp"

namespace cppts {
	
template<class TDur>
PeriodicityCondition<TDur>::PeriodicityCondition(duration_t period) : _required_period(period)
{ }

template<class TDur>
bool PeriodicityCondition<TDur>::is_achievable() const {
	return true;
}

template<class TDur>
bool PeriodicityCondition<TDur>::is_met(const TriggerState& state) const {
	auto now = std::chrono::steady_clock::now();
	auto countdown = state.get_countdown();

	return
		std::chrono::duration_cast<duration_t>(now - countdown) >= _required_period;
}

template<class TDur>
void PeriodicityCondition<TDur>::handle_repetition() { }

template<class TDur>
std::unique_ptr<ITriggerCondition> PeriodicityCondition<TDur>::clone() const {
	return std::make_unique<PeriodicityCondition<TDur>>(_required_period);
}

} // namespace cppts