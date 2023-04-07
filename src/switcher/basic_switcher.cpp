#include "func_objects/switcher/basic_switcher.hpp"

namespace cppts {

BasicSwitcher::BasicSwitcher() :
	_is_enabled(true),
	_is_turned_on(true)
{ }

void BasicSwitcher::enable() {
	_is_enabled = true;
}

void BasicSwitcher::disable() {
	_is_enabled = false;
	_is_turned_on = false;
}

void BasicSwitcher::turn_on() {
	if (_is_enabled) {
		_is_turned_on = true;
	}
}

void BasicSwitcher::turn_off() {
	if (_is_enabled) {
		_is_turned_on = false;
	}
}

BasicSwitcher::~BasicSwitcher() {
	disable();
}

bool BasicSwitcher::is_enabled_derived() const {
	return _is_enabled;
}

bool BasicSwitcher::is_turned_on_derived() const {
	return _is_turned_on;
}

} // namespace cppts