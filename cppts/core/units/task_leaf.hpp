#pragma once

#include <iostream>
#include <mutex>
#include "task_executer.hpp"
#include "../../func_objects/task/task.hpp"
#include "../../func_objects/task/state/task_state.hpp"
#include "unit_processable.hpp"

namespace cppts {

class TaskLeaf final : public IUnitProcessable {
public:
	TaskLeaf() = delete;
	TaskLeaf(
		TaskExecutionPolicy policy,
		size_t max_pool_sz,
		std::shared_ptr<ITask> task,
		std::shared_ptr<TaskState> state
	);

	bool is_active() const override final;

	bool is_full() const;

	void start();

	~TaskLeaf();

private:
	void process_base() override final;

private:
	TaskExecutionPolicy _policy;
	size_t _max_pool_size;

	std::list<TaskExecuter> _executers;
	std::mutex _executers_mutex;

	std::shared_ptr<ITask> _task;
	std::shared_ptr<TaskState> _state;
};

} // namespace cppts