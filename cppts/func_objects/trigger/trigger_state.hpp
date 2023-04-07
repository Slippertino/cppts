#pragma once

#include <string>
#include <atomic>
#include <chrono>
#include "trigger_status_type.hpp"

namespace cppts {

class TriggerState {
public:
	TriggerState() = delete;
	TriggerState(const std::string& name);

	TriggerStatusType get_status() const;

	std::chrono::steady_clock::time_point get_countdown() const;

	std::string get_name() const;

	void set_status(TriggerStatusType st);

	void reset();

private:
	std::string _name;
	std::atomic<TriggerStatusType> _status;
	std::chrono::steady_clock::time_point _countdown;
};

} // namespace cppts