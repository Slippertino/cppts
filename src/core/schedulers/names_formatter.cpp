#include "core/schedulers/names_formatter.hpp"

namespace cppts {

std::string NamesFormatter::apply_block_name_style(
	const std::string& scheduler_name,
	const std::string& trigger_name,
	const std::string& addition
) {
	return scheduler_name + "." + trigger_name + addition + _block_name_suffix;
}

std::string NamesFormatter::apply_with_condition_block_name_style(
	const std::string& scheduler_name,
    const std::string& trigger_name,
	const std::function<bool(const std::string&)> pred
) {
	auto base = scheduler_name + "." + trigger_name;

	auto num = Generator<uint64_t>::generate(
		std::numeric_limits<uint64_t>::min(),
		std::numeric_limits<uint64_t>::max(),
		[&](uint64_t gen) { 
			auto temp = NamesFormatter::apply_block_name_style(
				scheduler_name,
				trigger_name,
				std::to_string(gen)
			);

			return pred(temp);
		}
	);

	return NamesFormatter::apply_block_name_style(
		scheduler_name,
		trigger_name,
		std::to_string(num)
	);
}

std::string NamesFormatter::apply_trigger_name_style(const std::string& name) {
	return name + _trigger_name_suffix;
}

std::string NamesFormatter::apply_task_name_style(const std::string& name) {
	return name + _task_name_suffix;
}

std::string NamesFormatter::apply_task_endpoint_style(
	const std::string& block_name,
	const std::string& task_name
) {
	return block_name + "." + NamesFormatter::apply_task_name_style(task_name);
}

const std::string NamesFormatter::_block_name_suffix = "_block";
const std::string NamesFormatter::_trigger_name_suffix = "_trigger";
const std::string NamesFormatter::_task_name_suffix = "_task";

} // namespace cppts
