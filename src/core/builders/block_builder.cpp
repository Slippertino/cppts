#pragma once

#include "core/builders/block_builder.hpp"
#include "core/schedulers/task_scheduler_base.hpp"

namespace cppts {

BlockBuilder::BlockBuilder(TaskSchedulerBase* target) :
    _target(target),
    _trigger_name(target->_settings.default_trigger.name)
{ }

BlockBuilder& BlockBuilder::set_trigger(const std::string& name) {
    _trigger_name = name;

    return *this;
}

BlockBuilder& BlockBuilder::add_task(TaskInfo&& task) {
    _tasks.push_back(std::move(task));

    return *this;
}

std::string BlockBuilder::build() {
    auto block_name = _target->start_forming_block(_trigger_name);

    for (auto& tsk : _tasks) {
        _target->attach_task(block_name, std::move(tsk));
    }

    _target->finish_forming_block(block_name);

    return block_name;
}

} // namespace cppts