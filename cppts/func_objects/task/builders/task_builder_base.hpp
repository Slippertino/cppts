#pragma once

#include <thread>
#include <memory>
#include "../task_info.hpp"

namespace cppts {

template<class TBuilder>
class TaskBuilderBase {
public:
	TaskBuilderBase() = default;
	TaskBuilderBase(TaskInfo&& info);

	TBuilder& name(std::string nm);

	TBuilder& policy(TaskExecutionPolicy pol);

	TBuilder& max_pool_size(size_t sz);

	template<
		class TLogger,
		class... Args,
		class = std::enable_if_t<
			std::is_base_of_v<ILogger, TLogger> &&
			std::is_constructible_v<TLogger, Args...>
		>
	>
	TBuilder& emplace_logger(Args&&... args);

	TBuilder& logger(std::shared_ptr<ILogger> lgr);

	TaskInfo build();

protected:
	virtual void build_from_derived() = 0;

protected:
	TaskInfo _info;
};

} // namespace cppts

#include "task_builder_base_impl.hpp"