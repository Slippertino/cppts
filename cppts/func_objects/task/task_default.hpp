#pragma once

#include <functional>
#include "task_base.hpp"

namespace cppts {

class TaskDefaultBuilder;

class TaskDefault final : public TaskBase {

	friend class TaskDefaultBuilder;

	using context_t = std::function<TaskResult()>;
	using success_t = std::function<void()>;
	using fail_t = std::function<void(const std::exception&)>;

public:
	static TaskDefaultBuilder create();

private:
	TaskDefault() = default;

	void apply_context_derived(const TaskExecutionContext& context) override final;

	TaskResult execute_derived() override final;

	void on_success_derived() override final;

	void on_fail_derived(const std::exception& ex) override final;

private:
	std::function<TaskResult()> _context_handler = []() { return std::make_shared<TaskEmptyResult>(); };
	success_t _success_handler = []() {};
	fail_t _fail_handler = [](const std::exception&) {};
};

} // namespace cppts
