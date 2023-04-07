#include "core/builders/task_scheduler_base_builder.hpp"

namespace cppts {

template<class TDerivedBuilder>
TDerivedBuilder& TaskSchedulerBaseBuilder<TDerivedBuilder>::name(const std::string& nm) {
	_info.name = nm;

	return *static_cast<TDerivedBuilder*>(this);
}

template<class TDerivedBuilder>
TDerivedBuilder& TaskSchedulerBaseBuilder<TDerivedBuilder>::default_trigger(TriggerInfo&& tg) {
	_info.default_trigger = std::move(tg);

	return *static_cast<TDerivedBuilder*>(this);
}

template<class TDerivedBuilder>
TDerivedBuilder& TaskSchedulerBaseBuilder<TDerivedBuilder>::logger(std::shared_ptr<ILogger> logger) {
	_info.logger = std::make_shared<Logger>(logger);

	return *static_cast<TDerivedBuilder*>(this);
}

template<class TDerivedBuilder>
TDerivedBuilder& TaskSchedulerBaseBuilder<TDerivedBuilder>::switcher(std::shared_ptr<ISwitcher> switcher) {
	_info.switcher = switcher;

	return *static_cast<TDerivedBuilder*>(this);
}

} // namespace cppts