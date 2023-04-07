#pragma once

#include <type_traits>
#include <string>
#include "../../tools/generator.hpp"

namespace cppts {

class NamesFormatter {
public:
	static std::string apply_block_name_style(
		const std::string& scheduler_name,
		const std::string& trigger_name,
		const std::string& addition
	);

	static std::string apply_with_condition_block_name_style(
		const std::string& scheduler_name,
        const std::string& trigger_name,
		const std::function<bool(const std::string&)> pred
	);

	static std::string apply_trigger_name_style(const std::string& name);

	static std::string apply_task_name_style(const std::string& name);

	static std::string apply_task_endpoint_style(
		const std::string& block_name,
		const std::string& task_name
	);

private:
	static const std::string _block_name_suffix;
	static const std::string _trigger_name_suffix;
	static const std::string _task_name_suffix;
};

} // namespace cppts
