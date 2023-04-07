#pragma once

#include <memory>
#include "../../switcher/switcher.hpp"
#include "../trigger.hpp"

namespace cppts {

class DependencyCondition final : public ITriggerCondition {
public:
	DependencyCondition() = delete;
	DependencyCondition(std::shared_ptr<ISwitcherStateProvider> base = nullptr);

	bool is_achievable() const override final;

	bool is_met(const TriggerState& state) const override final;

	void handle_repetition() override final;

	std::unique_ptr<ITriggerCondition> clone() const override final;

private:
	std::shared_ptr<ISwitcherStateProvider> _base;
};

} // namespace cppts