#pragma once

#include "func_objects/task/builders/task_default_builder.hpp"
#include "func_objects/task/task_default.hpp"

namespace cppts {

TaskDefaultBuilder TaskDefault::create() {
	return TaskDefaultBuilder();
}

void TaskDefault::apply_context_derived(const TaskExecutionContext& context) { 
	_context_handler = context.args.get<context_t>("context");

	if (context.args.is_exist("success")) {
		_success_handler = context.args.get<success_t>("success");
	}

	if (context.args.is_exist("fail")) {
		_fail_handler = context.args.get<fail_t>("fail");
	}
}

TaskResult TaskDefault::execute_derived() {
	return _context_handler();
}

void TaskDefault::on_success_derived() {
	_success_handler();
}

void TaskDefault::on_fail_derived(const std::exception& ex) {
	_fail_handler(ex);
}

} // namespace cppts
