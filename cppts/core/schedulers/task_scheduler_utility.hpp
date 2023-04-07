#pragma once

#include <memory>
#include <string>
#include "../units/block_composite.hpp"

namespace cppts {

class ITaskSchedulerUtility {

	friend class TaskSchedulerBase;

protected:
	virtual bool is_block_registered(
		const std::string ts_name,
		const std::string& block_name
	) const = 0;

	virtual bool try_register_scheduler(const std::string& ts_name) = 0;
	virtual void unregister_scheduler(const std::string& ts_name) = 0;

	virtual std::string generate_block_name(
		const std::string& ts_name,
		const std::string& trigger_name,
		std::function<bool(const std::string&)> pred
	) const = 0;

	virtual void register_block(
		const std::string& ts_name,
		const std::string& block_name,
		std::shared_ptr<BlockComposite> block
	) = 0;
};

} // namespace cppts