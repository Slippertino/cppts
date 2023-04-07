#pragma once

#include <stdexcept>
#include "../trigger_condition.hpp"

namespace cppts {

class RepetitionsCondition final : public ITriggerCondition {
public:
	RepetitionsCondition() = delete;
	RepetitionsCondition(size_t reps_count, bool is_forever);

	bool is_achievable() const override final;

	bool is_met(const TriggerState& state) const override final;

	void handle_repetition() override final;

	std::unique_ptr<ITriggerCondition> clone() const override final;

private:
	bool _is_forever;
	size_t _rest_repetitions_count;
};

} // namespace cppts