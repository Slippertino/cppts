#pragma once

#include <string>
#include "task_scheduler_utility.hpp"
#include "task_scheduler_parameters.hpp"
#include "names_formatter.hpp"
#include "../builders/block_builder.hpp"
#include "../containers/forming_blocks_container.hpp"
#include "../containers/registered_triggers_container.hpp"
#include "func_objects/task/state/task_state_provider.hpp"
#include "func_objects/task/task_info.hpp"
#include "func_objects/task/builders/task_builders.hpp"
#include "func_objects/trigger/trigger_info.hpp"
#include "func_objects/switcher/basic_switcher.hpp"
#include "../exceptions.hpp"

namespace cppts {

class TaskSchedulerBase {
	
	friend class BlockBuilder;

public:
	bool is_active() const;

	virtual void run();
	virtual void stop();

	template<class TResult>
	std::shared_ptr<TaskStateProvider<TResult>> get_state(
		const std::string& block_name,
		const std::string& task_name
	) const {
		auto ep = NamesFormatter::apply_task_endpoint_style(block_name, task_name);

		return std::static_pointer_cast<TaskStateProvider<TResult>>(
			_tasks_states.at(ep)
		);
	}

	bool try_add_trigger(TriggerInfo&& trigger);

	BlockBuilder add_block();

	void wait_until_block_exist(const std::string& block_name) const;

	bool is_block_exist(const std::string& block_name) const;

	virtual ~TaskSchedulerBase();

protected:
	TaskSchedulerBase() = default;
	TaskSchedulerBase(
		std::shared_ptr<TaskSchedulerBase> parent,
		TaskSchedulerParameters&& settings
	);

	virtual void init(
		std::shared_ptr<TaskSchedulerBase> parent,
		TaskSchedulerParameters&& settings
	);

	template<class TEx, class... Args>
	void throw_exception(Args&&... args) {
		static_assert(std::is_constructible_v<TEx, Args...>, "try to throw unconstructible exception");

		auto ex = TEx(std::forward<Args>(args)...);

		TS_LOG(_settings.logger, FAIL) << ex.what() << "\n";

		throw ex;
	}

private:
	std::shared_ptr<ITaskSchedulerUtility> get_root();

	std::string start_forming_block(const std::string& trigger_name);

	void attach_task(
		const std::string& block_name,
		TaskInfo&& task
	);

	void finish_forming_block(const std::string& block_name);

protected:
	TaskSchedulerParameters _settings;

private:
	std::weak_ptr<ITaskSchedulerUtility> _root;

    RegisteredTriggersContainer _triggers;
	FormingBlocksContainer _forming_blocks;

	std::unordered_map<std::string, std::shared_ptr<void>> _tasks_states;
	std::mutex _task_states_mutex;
};

} // namespace cppts