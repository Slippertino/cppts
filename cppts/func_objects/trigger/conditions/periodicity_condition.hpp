#pragma once

#include <stdexcept>
#include "../trigger_condition.hpp"

namespace cppts {

template<class TDur>
class PeriodicityCondition final : public ITriggerCondition {

	using duration_t = typename TDur;

public:
	PeriodicityCondition() = delete;
	PeriodicityCondition(duration_t period);

	bool is_achievable() const override final;

	bool is_met(const TriggerState& state) const override final;

	void handle_repetition() override final;

	std::unique_ptr<ITriggerCondition> clone() const override final;

private:
	duration_t _required_period;
};

} // namespace cppts

#include "periodicity_condition_impl.hpp"