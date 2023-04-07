#pragma once

#include <memory>
#include "trigger_state.hpp"

namespace cppts {

class ITriggerCondition {
public:
	virtual bool is_achievable() const = 0;
	virtual bool is_met(const TriggerState&) const = 0;
	virtual void handle_repetition() = 0;
	virtual std::unique_ptr<ITriggerCondition> clone() const = 0;
};

} // namespace cppts