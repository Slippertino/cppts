#include "core/exceptions.hpp"

namespace cppts {

/*
* cppts_error
*/
DataStream cppts_error::error() const {
	DataStream::data_record_handler handler = [&](const std::string& msg) {
		_error_message = msg.c_str();
	};

	return DataStream(handler);
}

/*
* failed_ts_registration_error
*/
failed_ts_registration_error::failed_ts_registration_error(
	const std::string& name,
	const std::string& desc
) : _target_name(name), _error_desc(desc)
{ }

const char* failed_ts_registration_error::what() const noexcept {
	error() 
		<< "error: task scheduler with name [ " << _target_name << " ] " 
		<< "cannot be registered(" << _error_desc << ")";

	return _error_message;
}

/*
* nonexisten_root_ts_error
*/
const char* nonexisten_root_ts_error::what() const noexcept {
	error() << "error: root task scheduler has been already destroyed";

	return _error_message;
}

/*
* unknown_trigger_error
*/
unknown_trigger_error::unknown_trigger_error(const std::string& name)
	: _target_name(name)
{ }

const char* unknown_trigger_error::what() const noexcept {
	error()
		<< "error: detected a try to create block by unknown trigger "
		<< "with name [ " << _target_name << " ]";

	return _error_message;
}

/*
* invalid_task_name_error
*/
invalid_task_name_error::invalid_task_name_error(
	const std::string& scheduler_name,
	const std::string& block_name,
	const std::string& task_name
) : 
	_scheduler_name(scheduler_name),
	_block_name(block_name),
	_task_name(task_name)
{ }

const char* invalid_task_name_error::what() const noexcept {
	error()
		<< "error: task with name [ " << _task_name << " ] "
		<< "for block[" + _block_name + " ] "
		<< "in task scheduler[" + _scheduler_name + " ] "
		<< "has been already existed";

	return _error_message;
}

} // namespace cppts