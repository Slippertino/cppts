#pragma once

#include <string>
#include <vector>

namespace cppts {

class BlockBuilder {
public:
    BlockBuilder() = delete;
    BlockBuilder(class TaskSchedulerBase* target);

    BlockBuilder& set_trigger(const std::string& name);

    BlockBuilder& add_task(struct TaskInfo&& task);

    std::string build();

private:
    class TaskSchedulerBase* _target;
    std::string _trigger_name;
    std::vector<TaskInfo> _tasks;
};

} // namespace cppts