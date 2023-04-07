#pragma once

#include <stdexcept>
#include <memory>
#include <string>
#include <unordered_map>

namespace cppts {

class TaskArgumentsContainer {

	using argument_t = std::shared_ptr<void>;

public:
	TaskArgumentsContainer() = default;

	bool is_exist(std::string key) const;

	template<class T>
	void set(std::string key, T&& arg) {
		if (_container.find(key) != _container.end()) {
			throw std::invalid_argument("argument with key = " + key + " has already existed");
		}

		_container.insert({
			key,
			std::make_shared<typename std::decay<T>::type>(std::forward<T>(arg))
		});
	}

	template<class T>
	T get(std::string key) const {
		auto val = get_raw_value(key);

		return *static_cast<T*>(val.get());
	}

	template<class T>
	std::shared_ptr<T> get_ptr(std::string key) const {
		auto val = get_raw_value(key);

		return std::static_pointer_cast<T>(val);
	}

private:
	std::shared_ptr<void> get_raw_value(std::string key) const;

private:
	std::unordered_map<std::string, argument_t> _container;
};

} // namespace cppts