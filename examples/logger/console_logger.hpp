#pragma once

#include <iostream>
#include <mutex>
#include "core/logger/logger.hpp"

class ConsoleLogger : public cppts::ILogger {
public:
	void log_debug(const std::string& msg) override {
		std::lock_guard<std::mutex> locker(_output_stream_locker);

		std::cout << "[ DEBUG ] : " << msg << std::endl;
	}

	void log_info(const std::string& msg) override {
		std::lock_guard<std::mutex> locker(_output_stream_locker);

		std::cout << "[ INFO ] : " << msg << std::endl;
	}

	void log_fail(const std::string& msg) override {
		std::lock_guard<std::mutex> locker(_output_stream_locker);

		std::cout << "[ FAIL ] : " << msg << std::endl;
	}

private:
	std::mutex _output_stream_locker;
};