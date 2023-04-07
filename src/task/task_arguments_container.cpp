#include "func_objects/task/task_arguments_container.hpp"

namespace cppts {

bool TaskArgumentsContainer::is_exist(std::string key) const {
	return _container.find(key) != _container.end();
}

std::shared_ptr<void> TaskArgumentsContainer::get_raw_value(std::string key) const {
	if (_container.find(key) == _container.end()) {
		throw std::invalid_argument("argument with key = " + key + " does not exist");
	}

	return _container.at(key);
}

} // namespace cppts