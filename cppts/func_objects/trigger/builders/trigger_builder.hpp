#pragma once

#include "../trigger_info.hpp"
#include "../conditions/conditions.hpp"

namespace cppts {

class TriggerBuilder {
public:
	static TriggerBuilder create();

	static TriggerBuilder create(TriggerInfo&& info);

	TriggerBuilder& name(const std::string& nm);

	TriggerBuilder& forever();

	TriggerBuilder& repeats_count(size_t count);

	TriggerBuilder& predicate(const std::function<bool()>& pred);

	TriggerBuilder& depends_on(std::shared_ptr<ISwitcherStateProvider> switcher);

	TriggerBuilder& interval_ms(size_t count);

	TriggerBuilder& interval_sec(size_t count);

	TriggerBuilder& interval_min(size_t count);

	TriggerInfo build();

private:
	TriggerBuilder() = default;
	TriggerBuilder(TriggerInfo&& info);

	template<class TCond, class... Args>
	TriggerBuilder& add_condition(Args&&... args) {
		_info.conditions.push_back(
			std::make_unique<TCond>(std::forward<Args>(args)...)
		);

		return *this;
	}

private:
	TriggerInfo _info;
};

} // namespace cppts