#pragma once

#include <atomic>
#include "switcher.hpp"

namespace cppts {

class BasicSwitcher final : public ISwitcher {
public:
	BasicSwitcher();

	void enable() override final;

	void disable() override final;

	void turn_on() override final;

	void turn_off() override final;

	~BasicSwitcher();

private:
	bool is_enabled_derived() const override final;
	bool is_turned_on_derived() const override final;

private:
	std::atomic<bool> _is_enabled;
	std::atomic<bool> _is_turned_on;
};

} // namespace cppts