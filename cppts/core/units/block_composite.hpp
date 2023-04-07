#pragma once

#include <list>
#include <algorithm>
#include "unit_processable.hpp"
#include "task_leaf.hpp"
#include "../../func_objects/trigger/trigger.hpp"

namespace cppts {

class BlockComposite final : public IUnitProcessable {
public:
	BlockComposite() = delete;
	BlockComposite(TriggerInfo&& trigger);

	bool is_active() const override final;

	bool is_enabled() const;

	std::list<std::weak_ptr<IUnitProcessable>> get_tasks() const;

	void add_task_handler(std::shared_ptr<TaskLeaf> task);

private:
	bool have_free_space();

	void process_base() override final;

private:
	std::list<std::shared_ptr<TaskLeaf>> _tasks;
	std::mutex _tasks_mutex;

	Trigger _trigger;
};

} // namespace cppts
