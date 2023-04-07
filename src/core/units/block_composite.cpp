#include "core/units/block_composite.hpp"

namespace cppts {

BlockComposite::BlockComposite(TriggerInfo&& trigger) : _trigger(std::move(trigger))
{ }

bool BlockComposite::is_active() const {
	for (auto& u : _tasks) {
		if (u->is_active()) {
			return true;
		}
	}

	return false;
}

bool BlockComposite::is_enabled() const {
	return _trigger.get_status() != TriggerStatusType::Disabled;
}

std::list<std::weak_ptr<IUnitProcessable>> BlockComposite::get_tasks() const {
	std::list<std::weak_ptr<IUnitProcessable>> res;

	res.insert(res.end(), _tasks.begin(), _tasks.end());

	return res;
}

void BlockComposite::add_task_handler(std::shared_ptr<TaskLeaf> task) {
	std::lock_guard<std::mutex> locker(_tasks_mutex);

	_tasks.push_front(task);
}

bool BlockComposite::have_free_space() {
	for (auto& u : _tasks) {
		if (u->is_full()) {
			return false;
		}
	}

	return true;
}

void BlockComposite::process_base() {
	_trigger.update();

	auto tg_status = _trigger.get_status();

	switch (tg_status) {
	case TriggerStatusType::Disabled:
		break;
	case TriggerStatusType::Waiting:
		_trigger.start();
		break;
	case TriggerStatusType::Ready:

		if (have_free_space()) {
			for (auto& tsk : _tasks) {
				tsk->start();
			}

			_trigger.start();
		}

		break;
	}
}

} // namespace cppts