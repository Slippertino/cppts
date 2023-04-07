#pragma once

#include <string>

namespace cppts {

class ILogger {
public:
    virtual void log_debug(const std::string& msg) = 0;
    virtual void log_info(const std::string& msg) = 0;
    virtual void log_fail(const std::string& msg) = 0;
};

} // namespace cppts
