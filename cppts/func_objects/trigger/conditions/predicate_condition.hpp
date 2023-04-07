#pragma once

#include <functional>
#include "../trigger_condition.hpp"

namespace cppts {

class PredicateCondition final : public ITriggerCondition {
public:
	PredicateCondition() = delete;
	PredicateCondition(const std::function<bool()>& pred);

	bool is_achievable() const override final;

	bool is_met(const TriggerState& state) const override final;

	void handle_repetition() override final;

	std::unique_ptr<ITriggerCondition> clone() const override final;

private:
	std::function<bool()> _predicate;
};

} // namespace cppts