#pragma once

#include <unordered_map>
#include <memory>
#include "logging_type.hpp"
#include "logger_base.hpp"
#include "tools/data_stream.hpp"

namespace cppts {

class Logger {
public:
	Logger() = delete;
	Logger(std::shared_ptr<ILogger> base);

	DataStream get_stream(LoggingType type);

private:
    std::unordered_map<LoggingType, std::function<void(const std::string&)>> _logging_router;
	std::shared_ptr<ILogger> _base;
};

#define TS_LOG(logger_ptr, type) logger_ptr->get_stream(type)

} // namespace cppts
