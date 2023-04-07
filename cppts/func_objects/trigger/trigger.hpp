#pragma once

#include <atomic>
#include <memory>
#include <stdexcept>
#include <vector>
#include "trigger_condition.hpp"
#include "trigger_state.hpp"
#include "trigger_status_type.hpp"
#include "trigger_info.hpp"

namespace cppts {

class Trigger {

	using conditions_conatiner = std::vector<std::unique_ptr<ITriggerCondition>>;

public:
	Trigger() = delete;
	Trigger(TriggerInfo&& info);

	std::string get_name() const;

	TriggerStatusType get_status() const;

	bool is_ready() const;

	void start();

	void update();

private:
	bool is_valid() const;

	bool conditions_met() const;

private:
	TriggerState _state;
	std::vector<std::unique_ptr<ITriggerCondition>> _conditions;
};

} // namespace cppts