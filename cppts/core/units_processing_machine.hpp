#pragma once

#include <map>
#include <chrono>
#include <unordered_set>
#include <atomic>
#include "containers/processes_container.hpp"
#include "units/unit_processable.hpp"
#include "tools/generator.hpp"
#include "tools/processor_base.hpp"

using namespace std::chrono_literals;

namespace cppts {

class UnitsProcessingMachine : private IProcessorBase<std::map<std::string, ProcessesContainer>> {
public:
	void notify_scheduler_run(const std::string& scheduler_name);
	void notify_scheduler_stop(const std::string& scheduler_name);

	void set_concurrency_size(size_t sz);

	bool try_register_scheduler(const std::string& scheduler_name);
	void unregister_scheduler(const std::string& scheduler_name);

	ProcessesContainer& get_scheduler_processes(const std::string& scheduler_name);

private:
	void run();
	void stop();
	void restart();

	void working_loop();

	void process_base(std::pair<const std::string, ProcessesContainer>& obj) override;

private:
	std::atomic<size_t> _concurrency_size = 1;
	
    std::atomic<bool> _run = false;
	std::mutex _run_and_stop_sync;

	std::vector<std::thread> _working_threads;

	size_t _run_schedulers_count = 0;
	std::unordered_set<std::string> _active_schedulers_names;
	std::shared_mutex _active_schedulers_names_mutex;
};

} // namespace cppts
