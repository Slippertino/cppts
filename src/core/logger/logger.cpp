#include "core/logger/logger.hpp"

namespace cppts {

Logger::Logger(std::shared_ptr<ILogger> base) : _base(base) {
    _logging_router = {
        { DEBUG, [&](const std::string& msg) { _base->log_debug(msg); } },
        { INFO,  [&](const std::string& msg) { _base->log_info(msg);  } },
        { FAIL,  [&](const std::string& msg) { _base->log_fail(msg);  } }
    }; 
}

DataStream Logger::get_stream(LoggingType type) {
	return DataStream(_logging_router.at(type));
}

} // namespace cppts
