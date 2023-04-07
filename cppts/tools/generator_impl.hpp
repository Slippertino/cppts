#include "tools/generator.hpp"

namespace cppts {

template<class T, class Cond>
T Generator<T, Cond>::generate(T min, T max) {
	std::uniform_int_distribution<T> die{ min, max };
	return die(mersenne);
}

template<class T, class Cond>
T Generator<T, Cond>::generate(T min, T max, std::function<bool(T)> pred) {
	T res;

	do {
		res = generate(min, max);
	} while (!pred(res));

	return res;
}

template<class T, class Cond>
std::mt19937 Generator<T, Cond>::mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };


} // namespace cppts