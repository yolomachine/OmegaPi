#include <iomanip>
#include <fstream>

// https://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula
// do not confuse with
// https://en.wikipedia.org/wiki/Spigot_algorithm

template<int64_t base, int64_t exp>
struct pow_ {
	static constexpr int64_t value = base * pow_<base, exp - 1>::value;
};

template<int64_t base>
struct pow_<base, 0> {
	static constexpr int64_t value = 1;
};

template<int64_t K>
struct pi {
	static constexpr long double value =
		(1.0 / pow_<16, K>::value) * (
			4.0 / (8 * K + 1.0) - 2.0 / (8 * K + 4.0) -
			1.0 / (8 * K + 5.0) - 1.0 / (8 * K + 6.0)
		) + pi<K - 1>::value;
};

template<>
struct pi<0> {
	static constexpr long double value = 3.1333333333333;
};

// Limit: 50
constexpr int64_t N = 50;

int main() {
	std::ofstream out("31415926.pi", std::ofstream::out);
	out << std::setprecision(N + 1) << pi<15>::value << std::endl;
	out.close();
}