#pragma once

#include <iostream>
#include "cppts/cppts.hpp"
#include "logger/console_logger.hpp"
#include "func_objects/task/builders/task_custom_builder.hpp"

using namespace cppts;
using namespace std::chrono_literals;

class MyTask : public TaskBase {
public:
	static TaskCustomBuilder<MyTask> create() {
		return TaskCustomBuilder<MyTask>();
	}

protected:
	void apply_context_derived(const TaskExecutionContext& context) override {
		_value = context.args.get<int>("value");
	}

	TaskResult execute_derived() {
		std::cout << "My value: " << _value << std::endl;
		return wrap_result();
	}

	void on_success_derived() { }
	void on_fail_derived(const std::exception& ex) { }

private:
	int _value;
};

int main() {
	TaskScheduler::set_concurrency_size(1);

	auto logger = std::make_shared<ConsoleLogger>();

	auto scheduler = TaskScheduler::create()
		.name("my_scheduler")
		.logger(logger)
		.build();

	auto trigger = TriggerBuilder::create()
		.name("printer")
		.interval(1s)
		.repeats_count(5)
		.build();

	auto task = TaskBuilder::create<MyTask>()
		.name("hello_program")
		.logger(logger)
		.policy(ASYNC)
		.max_pool_size(1)
		.with_argument("value", 10)
		.build();

	scheduler->run();

	scheduler->try_add_trigger(trigger.clone());

	auto block = scheduler->add_block()
		.set_trigger(trigger.name)
		.add_task(std::move(task))
		.build();

	scheduler->wait_until_block_exist(block);
}