#pragma once

#include <string>
#include <exception>
#include "tools/data_stream.hpp"

namespace cppts {

class cppts_error : public std::exception
{ 
protected:
	DataStream error() const;

protected:
	mutable const char* _error_message;
};

class failed_ts_registration_error : public cppts_error {
public:
	failed_ts_registration_error() = delete;
	failed_ts_registration_error(
		const std::string& name,
		const std::string& desc
	);

	const char* what() const noexcept override;

private:
	std::string _target_name;
	std::string _error_desc;
};

class nonexisten_root_ts_error : public cppts_error {
public:
	const char* what() const noexcept override;
};

class unknown_trigger_error : public cppts_error {
public:
	unknown_trigger_error() = delete;
	unknown_trigger_error(const std::string& name);

	const char* what() const noexcept override;

private:
	std::string _target_name;
};

class invalid_task_name_error : public cppts_error {
public:
	invalid_task_name_error() = delete;
	invalid_task_name_error(
		const std::string& scheduler_name,
		const std::string& block_name, 
		const std::string& tsk_name
	);

	const char* what() const noexcept override;

private:
	std::string _scheduler_name;
	std::string _block_name;
	std::string _task_name;
};

} // namespace cppts