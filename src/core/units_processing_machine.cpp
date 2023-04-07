#include "core/units_processing_machine.hpp"

namespace cppts {

void UnitsProcessingMachine::notify_scheduler_run(const std::string& scheduler_name) {
	std::lock_guard<std::mutex> locker(_run_and_stop_sync);

	++_run_schedulers_count;

	_active_schedulers_names_mutex.lock();
	_active_schedulers_names.insert(scheduler_name);
	_active_schedulers_names_mutex.unlock();

	if (!_run) {
		run();
	}
}

void UnitsProcessingMachine::notify_scheduler_stop(const std::string& scheduler_name) {
	std::lock_guard<std::mutex> locker(_run_and_stop_sync);

	--_run_schedulers_count;

	_active_schedulers_names_mutex.lock();
	_active_schedulers_names.erase(scheduler_name);
	_active_schedulers_names_mutex.unlock();

	if (_run && !_run_schedulers_count) {
		stop();
	}
}

void UnitsProcessingMachine::run() {
    if (_run) {
        return;
    }

	_run = true;

	for (auto i = 0; i < _concurrency_size; ++i) {
		auto th = std::thread(&UnitsProcessingMachine::working_loop, this);
		_working_threads.push_back(std::move(th));
	}
}

void UnitsProcessingMachine::stop() {
    if (!_run) {
        return;
    }

	_run = false;

	for (auto i = 0; i < _working_threads.size(); ++i) {
		_working_threads[i].join();
	}

	_working_threads.clear();
}

void UnitsProcessingMachine::restart() {
	std::lock_guard<std::mutex> locker(_run_and_stop_sync);

    if (_run) {
        stop();
        run();
    }
}

void UnitsProcessingMachine::set_concurrency_size(size_t sz) {
	_concurrency_size = sz;

    restart();
}

bool UnitsProcessingMachine::try_register_scheduler(const std::string& scheduler_name) {
	std::lock_guard<std::shared_mutex> locker(_target_mutex);

	if (_target.find(scheduler_name) != _target.end()) {
		return false;
	}

	_target.insert({scheduler_name, ProcessesContainer() });

	return true;
}

void UnitsProcessingMachine::unregister_scheduler(const std::string& scheduler_name) {
	std::lock_guard<std::shared_mutex> locker(_target_mutex);

	_target.erase(scheduler_name);
}

ProcessesContainer& UnitsProcessingMachine::get_scheduler_processes(const std::string& nm) {
	_target_mutex.lock_shared();

	auto& res = _target.at(nm);

	_target_mutex.unlock_shared();

	return res;
}

void UnitsProcessingMachine::working_loop() {
	while (_run) {
		process();
		std::this_thread::yield();
	}
}

void UnitsProcessingMachine::process_base(std::pair<const std::string, ProcessesContainer>& obj) {
	_active_schedulers_names_mutex.lock();
	auto is_active = _active_schedulers_names.find(obj.first) != _active_schedulers_names.cend();
	_active_schedulers_names_mutex.unlock();

	if (is_active) {
		obj.second.update();
		obj.second.process();
	}
}

} // namespace cppts