#pragma once

#include <functional>
#include <random>

namespace cppts {

template<class T, class = std::enable_if_t<std::is_integral_v<T>>>
class Generator {
public:
	static T generate(T min, T max);
	static T generate(T min, T max, std::function<bool(T)> pred);

private:
	static std::mt19937 mersenne;
};

} // namespace cppts

#include "generator_impl.hpp"
