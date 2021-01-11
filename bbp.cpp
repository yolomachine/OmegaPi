#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

// https://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula
// do not confuse with
// https://en.wikipedia.org/wiki/Spigot_algorithm

#ifdef __int128
// Limit: 62
static constexpr auto N = 62;
static constexpr auto K = 31;
using int_t = unsigned __int128;
#else
// Limit: 50
static constexpr auto N = 50;
static constexpr auto K = 15;
using int_t = uint64_t;
#endif

template<int_t base, int_t exp>
struct pow_ {
	static constexpr int_t value = base * pow_<base, exp - 1>::value;
};

template<int_t base>
struct pow_<base, 0> {
	static constexpr int_t value = 1;
};

template<int_t K>
struct pi {
	static constexpr long double value =
		(1.0 / pow_<16, K>::value) * (
			4.0 / (8 * K + 1.0) - 2.0 / (8 * K + 4.0) -
			1.0 / (8 * K + 5.0) - 1.0 / (8 * K + 6.0)
		) + pi<K - 1>::value;
};

template<>
struct pi<0> {
	static constexpr long double value = 4.0L - 0.5L - 1.0L / 5.0L - 1.0L / 6.0L;
};

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	std::ofstream out("31415926.pi", std::ofstream::out);
	out << std::fixed << std::setprecision(N) << pi<K>::value << std::endl;
	out.close();
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Run time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms, haha templates are fun\n";
}