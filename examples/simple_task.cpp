#pragma once

#include <iostream>
#include "cppts/cppts.hpp"
#include "logger/console_logger.hpp"

using namespace cppts;
using namespace std::chrono_literals;

std::shared_ptr<TaskScheduler> scheduler;

int main() {
	TaskScheduler::set_concurrency_size(10);

	auto logger = std::make_shared<ConsoleLogger>();

	scheduler = TaskScheduler::create()
		.name("my_scheduler")
		.logger(logger)
		.build();

	auto trigger = TriggerBuilder::create()
		.name("printer")
		.interval(500ms)
		.repeats_count(10)
		.build();

	auto task = TaskBuilder::create<TaskDefault>()
		.name("hello_printer")
		.logger(logger)
		.policy(ASYNC)
		.max_pool_size(1)
		.set_task<void>([]() { std::cout << "Hello world!\n"; })
		.set_success_handler([]() {std::cout << "Success!\n"; })
		.build();

	scheduler->try_add_trigger(trigger.clone());

	auto block = scheduler->add_block()
		.set_trigger(trigger.name)
		.add_task(std::move(task))
		.build();

	scheduler->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	scheduler->stop();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	scheduler->run();

	scheduler->wait_until_block_exist(block);
}