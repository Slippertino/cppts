#pragma once

#include <memory>
#include <thread>
#include <type_traits>
#include <stdexcept>
#include "../schedulers/task_scheduler_parameters.hpp"

namespace cppts {

template<class TDerivedBuilder>
class TaskSchedulerBaseBuilder {
public:
	TDerivedBuilder& name(const std::string& nm);

	TDerivedBuilder& default_trigger(TriggerInfo&& tg);

	TDerivedBuilder& logger(std::shared_ptr<ILogger> logger);

	template<
		class TLogger,
		class... Args,
		class = std::enable_if_t<
			std::is_base_of_v<ILogger, TLogger>&&
			std::is_constructible_v<TLogger, Args...>
		>
	>
	TDerivedBuilder& emplace_logger(Args&&... args) {
		_info.logger = std::make_shared<Logger>(
			std::make_shared<TLogger>(std::forward<Args>(args)...)
		);

		return *static_cast<TDerivedBuilder*>(this);
	}

	TDerivedBuilder& switcher(std::shared_ptr<ISwitcher> switcher);

	template<
		class TSwitcher,
		class... Args,
		class = std::enable_if_t<
			std::is_base_of_v<ISwitcher, TSwitcher>&&
			std::is_constructible_v<ISwitcher, Args...>
		>
	>
	TDerivedBuilder& emplace_switcher(Args&&... args) {
		_info.switcher = std::make_shared<TSwitcher>(std::forward<Args>(args)...);

		return *static_cast<TDerivedBuilder*>(this);
	}

protected:
	TaskSchedulerBaseBuilder() {
		static_assert(
			std::is_base_of_v<TaskSchedulerBaseBuilder<TDerivedBuilder>, TDerivedBuilder>,
			"any scheduler builder must be inherited from TaskSchedulerBaseBuilder"
		);
	}

	virtual ~TaskSchedulerBaseBuilder() = default;

protected:
	TaskSchedulerParameters _info;
};

} // namespace cppts

#include "task_scheduler_base_builder_impl.hpp"