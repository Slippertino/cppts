#pragma once

#include "logger.hpp"

namespace cppts {

class DefaultLogger final : public ILogger {
public:
	void log_debug(const std::string& msg) override final;
	void log_info(const std::string& msg) override final;
	void log_fail(const std::string& msg) override final;
};

} // namespace cppts