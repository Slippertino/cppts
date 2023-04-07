#include "func_objects/switcher/switcher.hpp"

namespace cppts {

bool ISwitcher::is_enabled() const {
	auto res = is_enabled_derived();

	return _base
		? _base->is_enabled() && res
		: res;
}

bool ISwitcher::is_turned_on() const {
	auto res = is_turned_on_derived();

	return _base
		? _base->is_turned_on() && res
		: res;
}

void ISwitcher::reset_base(std::shared_ptr<ISwitcherStateProvider> base) {
	_base = base;
}

} // namespace cppts