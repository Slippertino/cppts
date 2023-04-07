#pragma once

namespace cppts {

class ISwitcherStateProvider {
public:
	virtual bool is_enabled() const = 0;
	virtual bool is_turned_on() const = 0;
};

} // namespace cppts