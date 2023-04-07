#pragma once

#include <type_traits>
#include "task_builder_base.hpp"

namespace cppts {

template<class TTask>
class TaskCustomBuilder : public TaskBuilderBase<TaskCustomBuilder<TTask>> {
public:
	template<class... Args>
	TaskCustomBuilder(Args&&... args) {
		static_assert(
			std::is_constructible_v<TTask, Args&&...>,
			"unsuitable args to construct task"
		);

		auto task = new TTask(std::forward<Args>(args)...);
		_info.image = std::shared_ptr<TTask>(task);
	}

	TaskCustomBuilder(TaskInfo&& info) : TaskBuilderBase<TaskCustomBuilder>(std::move(info)) { 
		static_assert(
			std::is_convertible_v<decltype(_info.image.get()), TTask*>(),
			"unsuitable type to convert to TTask*"
		);
	}

	template<class TArg>
	TaskCustomBuilder& with_argument(std::string key, TArg&& arg) {
		_info.args.set(key, std::move(arg));
		return *this;
	}

protected:
	void build_from_derived() override { }
};

} // namespace cppts