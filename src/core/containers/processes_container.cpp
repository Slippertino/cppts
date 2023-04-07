#include "core/containers/processes_container.hpp"

namespace cppts {

ProcessesContainer::ProcessesContainer(ProcessesContainer&& pc) {
	_processes_to_add.splice(
		_processes_to_add.end(),
		std::move(pc._processes_to_add)
	);
}

void ProcessesContainer::add(std::list<std::weak_ptr<IUnitProcessable>>&& new_processes) {
	std::lock_guard<std::mutex> locker{ _processes_to_add_mutex };

	_processes_to_add.splice(
		_processes_to_add.end(),
		std::move(new_processes)
	);
}

void ProcessesContainer::process_base(std::weak_ptr<IUnitProcessable>& obj) {
	if (auto ptr = obj.lock()) {
		ptr->process();
	}
}

void ProcessesContainer::update() {
	if (!_target_mutex.try_lock()) {
		return;
	}

	std::lock_guard<std::mutex> locker{ _processes_to_add_mutex };

	_target.splice(_target.end(), _processes_to_add);
	_target.remove_if([](auto& proc) { return proc.expired(); });

	_target_mutex.unlock();
}

} // namespace cppts