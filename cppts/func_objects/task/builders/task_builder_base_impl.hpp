#include "func_objects/task/builders/task_builder_base.hpp"

namespace cppts {

template<class TBuilder>
TaskBuilderBase<TBuilder>::TaskBuilderBase(TaskInfo&& info) : _info(info)
{ }

template<class TBuilder>
TBuilder& TaskBuilderBase<TBuilder>::name(std::string nm) {
	_info.name = nm;
	return *static_cast<TBuilder*>(this);
}

template<class TBuilder>
TBuilder& TaskBuilderBase<TBuilder>::policy(TaskExecutionPolicy pol) {
	_info.policy = pol;

	return *static_cast<TBuilder*>(this);
}

template<class TBuilder>
TBuilder& TaskBuilderBase<TBuilder>::max_pool_size(size_t sz) {
	if (sz == 0) {
		throw std::invalid_argument("size of task pool cannot be equal zero");
	}

	_info.max_pool_size = sz;

	return *static_cast<TBuilder*>(this);
}

template<class TBuilder>
template<class TLogger, class... Args, class Cond>
TBuilder& TaskBuilderBase<TBuilder>::emplace_logger(Args&&... args) {
	_info.logger = std::make_shared<Logger>(
		std::make_shared<TLogger>(std::forward<Args>(args)...)
	);

	return *static_cast<TBuilder*>(this);
}

template<class TBuilder>
TBuilder& TaskBuilderBase<TBuilder>::logger(std::shared_ptr<ILogger> lgr) {
	_info.logger = std::make_shared<Logger>(lgr);

	return *static_cast<TBuilder*>(this);
}

template<class TBuilder>
TaskInfo TaskBuilderBase<TBuilder>::build() {
	build_from_derived();
	return std::move(_info);
}

} // namespace cppts