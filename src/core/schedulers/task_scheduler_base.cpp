#pragma once

#include "core/schedulers/task_scheduler_base.hpp"
#include "core/builders/block_builder.hpp"

namespace cppts {

bool TaskSchedulerBase::is_active() const {
	auto& sw = _settings.switcher;

	return sw->is_enabled() && sw->is_turned_on();
}

void TaskSchedulerBase::run() {
	_settings.switcher->turn_on();
}

void TaskSchedulerBase::stop() {
	_settings.switcher->turn_off();
}

bool TaskSchedulerBase::try_add_trigger(TriggerInfo&& trigger) {
	auto tg_old_name = trigger.name;
	auto tg_new_name = NamesFormatter::apply_trigger_name_style(tg_old_name);

	auto updated_tg = TriggerBuilder::create(std::move(trigger))
		.name(tg_new_name)
		.depends_on(_settings.switcher)
		.build();

	auto res = _triggers.try_add(std::move(updated_tg));

	if (res) {
		TS_LOG(_settings.logger, INFO)
			<< "New trigger [ " << tg_new_name << " ] was successfully registered in TS [ " << _settings.name << " ].";
	} else {
		TS_LOG(_settings.logger, DEBUG)
			<< "Failed to register new trigger [ " << tg_new_name << " ] in TS [ " << _settings.name << " ].";
	}

	return res;
}

BlockBuilder TaskSchedulerBase::add_block() {
	return BlockBuilder(this);
}

void TaskSchedulerBase::wait_until_block_exist(const std::string& nm) const {
	while (is_block_exist(nm)) {
		std::this_thread::yield();
	}
}

bool TaskSchedulerBase::is_block_exist(const std::string& block_name) const {
	if (auto root = _root.lock()) {
		return root->is_block_registered(_settings.name, block_name);
	}

	return false;
}

TaskSchedulerBase::~TaskSchedulerBase() {
	_settings.switcher->disable();

	stop();

	if (auto root = _root.lock()) {
		root->unregister_scheduler(_settings.name);
	}
}

TaskSchedulerBase::TaskSchedulerBase(
	std::shared_ptr<TaskSchedulerBase> parent,
	TaskSchedulerParameters&& settings
) {
	init(parent, std::move(settings));
}

void TaskSchedulerBase::init(
	std::shared_ptr<TaskSchedulerBase> parent,
	TaskSchedulerParameters&& settings
) {
	_settings = std::move(settings);
	_settings.switcher->enable();

	if (this == parent.get()) {
		_root = std::dynamic_pointer_cast<ITaskSchedulerUtility>(parent);
	}
	else {
		_root = parent->_root;
		_settings.switcher->reset_base(parent->_settings.switcher);
	}

	auto root = get_root();

	if (!root->try_register_scheduler(_settings.name)) {
		throw_exception<failed_ts_registration_error>(
			_settings.name,
			"ts with such name has been already registered"
		);
	}

	try_add_trigger(_settings.default_trigger.clone());
}

std::shared_ptr<ITaskSchedulerUtility> TaskSchedulerBase::get_root() {
	std::shared_ptr<ITaskSchedulerUtility> res;

	if (res = _root.lock()) {
		return res;
	}

	throw_exception<nonexisten_root_ts_error>();
	throw;
}

std::string TaskSchedulerBase::start_forming_block(const std::string& trigger_name) {
	auto root = get_root();

	auto real_tg_name = NamesFormatter::apply_trigger_name_style(trigger_name);

	if (!_triggers.is_exist(real_tg_name)) {
		throw_exception<unknown_trigger_error>(real_tg_name);
	}

	auto tg_info = _triggers.get(real_tg_name);

	auto block_name = _forming_blocks.add_block(
		std::move(tg_info),
		[&]() {
			return root->generate_block_name(
				_settings.name,
				real_tg_name,
				[&](const std::string& bn) { return !_forming_blocks.is_exist(bn); }
			);
		}
	);

	TS_LOG(_settings.logger, INFO) << "Start forming block for TS [ " << _settings.name << " ] : " << block_name;

	return block_name;
}

void TaskSchedulerBase::attach_task(
	const std::string& block_name,
	TaskInfo&& task
) {
	if (!task.logger) {
		task.logger = _settings.logger;
	}

	task.name = NamesFormatter::apply_task_endpoint_style(block_name, task.name);

	if (!_forming_blocks.try_add_task(block_name, std::move(task))) {
		throw_exception<invalid_task_name_error>(
			_settings.name,
			block_name,
			task.name
		);
	}

	TS_LOG(_settings.logger, INFO) 
		<< "Added new task [ " << task.name << " ] "
		<< "for block [ " << block_name << " ] " 
		<< "in TS [ " << _settings.name << " ]";
}

void TaskSchedulerBase::finish_forming_block(const std::string& block_name) {
	auto root = get_root();

	auto block = _forming_blocks.get(block_name);

	root->register_block(
		_settings.name,
		block_name,
		block.block
	);

	_forming_blocks.erase(block_name);

	std::lock_guard<std::mutex> locker(_task_states_mutex);
	_tasks_states.insert(block.tasks_states.begin(), block.tasks_states.end());

	TS_LOG(_settings.logger, INFO) << "Finish forming block for TS [ " << _settings.name << " ] : " << block_name;
}

} // namespace cppts