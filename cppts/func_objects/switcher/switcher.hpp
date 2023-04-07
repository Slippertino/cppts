#pragma once

#include <memory>
#include <vector>
#include "switcher_state_provider.hpp"

namespace cppts {

class ISwitcher : public ISwitcherStateProvider {
public:
	bool is_enabled() const override final;
	bool is_turned_on() const override final;

	void reset_base(std::shared_ptr<ISwitcherStateProvider> base = nullptr);

	virtual void enable() = 0;
	virtual void disable() = 0;

	virtual void turn_on() = 0;
	virtual void turn_off() = 0;

	virtual ~ISwitcher() = default;

protected:
	virtual bool is_enabled_derived() const = 0;
	virtual bool is_turned_on_derived() const = 0;

private:
	std::shared_ptr<ISwitcherStateProvider> _base;
};

} // namespace cppts