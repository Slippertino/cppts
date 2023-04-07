#include "core/units/unit_processable.hpp"

namespace cppts {

void IUnitProcessable::process() {
	if (!_processing_sync.try_lock()) {
		return;
	}

	process_base();

	_processing_sync.unlock();
}

} // namespace cppts