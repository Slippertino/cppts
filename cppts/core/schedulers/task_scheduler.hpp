#pragma once

#include <shared_mutex>
#include "../units_processing_machine.hpp"
#include "../builders/task_scheduler_builder.hpp"
#include "../containers/processable_blocks_container.hpp"
#include "task_scheduler_base.hpp"
#include "func_objects/task/task_default.hpp"

namespace cppts {

class TaskScheduler final :
	public TaskSchedulerBase, 
	public ITaskSchedulerUtility {

	friend class TaskSchedulerBuilder;

public:
	static TaskSchedulerBuilder create();
	static void set_concurrency_size(size_t sz);

	void run() override final;
	void stop() override final;

	~TaskScheduler();

private:
	TaskScheduler() = default;

	void init(
		std::shared_ptr<TaskSchedulerBase> parent,
		TaskSchedulerParameters&& settings
	) override final;

	void add_system_block();

	bool is_block_registered(
		const std::string ts_name,
		const std::string& block_name
	) const override final;

	bool try_register_scheduler(const std::string& ts_name) override final;

	void unregister_scheduler(const std::string& ts_name) override final;

	std::string generate_block_name(
		const std::string& ts_name,
		const std::string& trigger_name,
		std::function<bool(const std::string&)> pred
	) const override final;

	void register_block(
		const std::string& ts_name,
		const std::string& block_name,
		std::shared_ptr<BlockComposite> block
	) override final;

private:
	inline static UnitsProcessingMachine _upm;

	std::unordered_map<std::string, ProcessableBlocksContainer> _scheduler_blocks_containers;
	mutable std::shared_mutex _scheduler_blocks_containers_mutex;
};

} // namespace cppts