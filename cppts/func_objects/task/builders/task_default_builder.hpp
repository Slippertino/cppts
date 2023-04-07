#pragma once

#include "task_builder_base.hpp"

namespace cppts {

class TaskDefaultBuilder final : public TaskBuilderBase<TaskDefaultBuilder> {

	using context_t = std::function<TaskResult()>;
	using success_t = std::function<void()>;
	using fail_t = std::function<void(const std::exception&)>;

public:
	TaskDefaultBuilder() = default;
	TaskDefaultBuilder(TaskInfo&& info);

	template<class TResult = void>
	TaskDefaultBuilder& set_task(const std::function<TResult()>& task) {
		if constexpr (std::is_same_v<TResult, void>) {
			_info.args.set<context_t>(
				"context", 
				[=]() { 
					task(); 
					return std::make_shared<TaskEmptyResult>(); 
				}
			);
		}
		else {
			_info.args.set<context_t>(
				"context",
				[=]() { 
					return std::make_shared<TResult>(task()); 
				}
			);
		}

		return *this;
	}

	TaskDefaultBuilder& set_success_handler(const success_t& success_handler);

	TaskDefaultBuilder& set_fail_handler(const fail_t& fail_handler);

protected:
	void build_from_derived() override final;
};

} // namespace cppts