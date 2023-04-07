#pragma once

#include "core/logger/default_logger.hpp"
#include "task.hpp"
#include "task_types.hpp"
#include "task_execution_context.hpp"

namespace cppts {

class TaskBase : public ITask {
public:
    void apply_context(const TaskExecutionContext& context) override final {
        _task_name = context.task_name;
        _block_name = context.block_name;
        _logger = context.logger;

        apply_context_derived(context);
    }

	TaskResult execute() override final {
	    TS_LOG(_logger, DEBUG)
		    << "Start executing task: "
		    << "[ " << _task_name << " ]";

        return execute_derived();
    }

	void on_success() override final {
        TS_LOG(_logger, DEBUG)
            << "Success handler for: "
            << "[ " << _task_name << " ]";

        on_success_derived();
    }
	
    void on_fail(const std::exception& ex) override final {
        TS_LOG(_logger, DEBUG)
            << "Fail handler for: "
            << "[ " << _task_name << " ]";

        on_fail_derived(ex);
    }

protected:
    virtual void apply_context_derived(const TaskExecutionContext& context) = 0;
    virtual TaskResult execute_derived() = 0;
    virtual void on_success_derived() = 0;
    virtual void on_fail_derived(const std::exception& ex) = 0;

    template<class T>
    TaskResult wrap_result(T&& res) {
        return std::make_shared<T>(std::forward<T>(res));
    }

    TaskResult wrap_result() {
        return std::make_shared<TaskEmptyResult>();
    }

protected:
    std::string _task_name = "unknown";
    std::string _block_name = "unknown";
    std::shared_ptr<Logger> _logger = std::make_shared<Logger>(
        std::make_shared<DefaultLogger>()
    );
};

} // namespace cppts
