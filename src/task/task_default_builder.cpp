#pragma once

#include "func_objects/task/builders/task_default_builder.hpp"
#include "func_objects/task/task_default.hpp"

namespace cppts {

TaskDefaultBuilder::TaskDefaultBuilder(TaskInfo&& info) :
	TaskBuilderBase<TaskDefaultBuilder>(std::move(info))
{ }

TaskDefaultBuilder& TaskDefaultBuilder::set_success_handler(const success_t& success_handler) {
	_info.args.set("success", success_handler);
	return *this;
}

TaskDefaultBuilder& TaskDefaultBuilder::set_fail_handler(const fail_t& fail_handler) {
	_info.args.set("fail", fail_handler);
	return *this;
}

void TaskDefaultBuilder::build_from_derived() { 
	auto task = new TaskDefault();

	_info.image = std::shared_ptr<TaskDefault>(task);
}

} // namespace cppts