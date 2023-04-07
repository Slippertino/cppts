#pragma once

#include <type_traits>
#include "../task.hpp"

namespace cppts {

class TaskBuilder {
public:
	template<
		class TTask,
		class = std::enable_if_t<
			std::is_base_of_v<ITask, TTask> &&
			!std::is_abstract_v<TTask>
		>
	>
	static decltype(std::declval<TTask>().create()) create() {
		return TTask::create();
	}
};

} // namespace cppts