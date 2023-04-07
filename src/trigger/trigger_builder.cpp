#include "func_objects/trigger/builders/trigger_builder.hpp"

namespace cppts {

TriggerBuilder TriggerBuilder::create() {
	return TriggerBuilder();
}

TriggerBuilder TriggerBuilder::create(TriggerInfo&& info) {
	return TriggerBuilder(std::move(info));
}

TriggerBuilder& TriggerBuilder::name(const std::string& nm) {
	_info.name = nm;
	return *this;
}

TriggerBuilder& TriggerBuilder::forever() {
	return add_condition<RepetitionsCondition>(0, true);
}

TriggerBuilder& TriggerBuilder::repeats_count(size_t count) {
	return add_condition<RepetitionsCondition>(count, false);
}

TriggerBuilder& TriggerBuilder::predicate(const std::function<bool()>& pred) {
	return add_condition<PredicateCondition>(pred);
}

TriggerBuilder& TriggerBuilder::depends_on(std::shared_ptr<ISwitcherStateProvider> switcher) {
	return add_condition<DependencyCondition>(switcher);
}

TriggerInfo TriggerBuilder::build() {
	return std::move(_info);
}

TriggerBuilder::TriggerBuilder(TriggerInfo&& info) : _info(std::move(info))
{ }

} // namespace cppts