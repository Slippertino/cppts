#pragma once

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include "tools/processor_base.hpp"
#include <list>
#include "../units/unit_processable.hpp"

namespace cppts {

class ProcessesContainer : public IProcessorBase<std::list<std::weak_ptr<IUnitProcessable>>> {
public:
	ProcessesContainer() = default;
	ProcessesContainer(ProcessesContainer&& pc);

	void add(std::list<std::weak_ptr<IUnitProcessable>>&& new_processes);

	void update();

private:
	void process_base(std::weak_ptr<IUnitProcessable>& obj) override;

private:
	std::list<std::weak_ptr<IUnitProcessable>> _processes_to_add;
	std::mutex _processes_to_add_mutex;
};

} // namespace cppts