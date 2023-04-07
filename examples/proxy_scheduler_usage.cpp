#pragma once

#include <iostream>
#include <chrono>
#include "cppts/cppts.hpp"
#include "logger/console_logger.hpp"

using namespace std::chrono_literals;
using namespace cppts;

std::shared_ptr<ILogger> logger;
std::shared_ptr<TaskScheduler> root_scheduler;
std::shared_ptr<TaskProxyScheduler> proxy_scheduler;

void init() {
	TaskScheduler::set_concurrency_size(8);

	logger = std::make_shared<ConsoleLogger>();

	root_scheduler = TaskScheduler::create()
		.name("my_scheduler")
		.logger(logger)
		.build();

	proxy_scheduler = TaskProxyScheduler::create()
		.name("my_proxy_scheduler")
		.logger(logger)
		.depends_on(root_scheduler)
		.build();
}

std::string fill_scheduler() {
	auto trigger = TriggerBuilder::create()
		.name("printer_root")
		.interval(2s)
		.repeats_count(5)
		.build();

	auto task = TaskBuilder::create<TaskDefault>()
		.name("hello_printer")
		.logger(logger)
		.max_pool_size(3)
		.set_task<void>([]() { std::cout << "Im in RootScheduler!\n"; })
		.build();

	root_scheduler->try_add_trigger(trigger.clone());

	auto block = root_scheduler->add_block()
		.set_trigger(trigger.name)
		.add_task(std::move(task))
		.build();

	return block;
}

std::string fill_proxy_scheduler() {
	auto trigger = TriggerBuilder::create()
		.name("printer_proxy")
		.interval(500ms)
		.repeats_count(20)
		.build();

	auto task = TaskBuilder::create<TaskDefault>()
		.name("hello_printer")
		.logger(logger)
		.max_pool_size(5)
		.set_task<void>([]() {
			static int a = 0;
			std::cout << "Im in ProxyScheduler! " << ++a << "\n";
		})
		.build();

	proxy_scheduler->try_add_trigger(trigger.clone());

	auto block = proxy_scheduler->add_block()
		.set_trigger(trigger.name)
		.add_task(std::move(task))
		.build();

	return block;
}

int main() {
	init();

	auto root_block = fill_scheduler();
	auto proxy_block = fill_proxy_scheduler();

	root_scheduler->run();
	proxy_scheduler->run();

	std::this_thread::sleep_for(3s);

	root_scheduler->stop();
	logger->log_info("........ R O O T    P A U S E ........");
	std::this_thread::sleep_for(5s);
	logger->log_info("........ R O O T    S T A R T ........");
	root_scheduler->run();

	proxy_scheduler->stop();
	logger->log_info("........ P R O X Y  P A U S E ........");
	std::this_thread::sleep_for(5s);
	logger->log_info("........ P R O X Y  S T A R T ........");
	proxy_scheduler->run();

	proxy_scheduler->wait_until_block_exist(proxy_block);
}