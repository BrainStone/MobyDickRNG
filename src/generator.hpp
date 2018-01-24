#pragma once

#include <map>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

template<typename T>
class discrete_mapped_distribution {
private:
	std::discrete_distribution<size_t> distr;
	std::vector<T> values;

public:
	discrete_mapped_distribution() :
		distr(), values() {
	}
	template<typename I, typename = typename std::enable_if<
			std::is_arithmetic<I>::value, I>::type>
	discrete_mapped_distribution(std::map<T, I> distribution) :
			values() {
		std::vector<I> counts = std::vector<I>();

		values.reserve(distribution.size());
		counts.reserve(distribution.size());

		for (typename std::map<T, I>::const_reference count : distribution) {
			values.push_back(count.first);
			counts.push_back(count.second);
		}

		distr = std::discrete_distribution<size_t>(counts.cbegin(), counts.cend());
	}

	discrete_mapped_distribution(const discrete_mapped_distribution&) = default;
	discrete_mapped_distribution& operator=(const discrete_mapped_distribution&) = default;

	template<typename URNG>
	T operator()(URNG& urng) {
		return values.at(distr(urng));
	}
};

class generator {
private:
	static discrete_mapped_distribution<std::string::value_type> letters;

	std::minstd_rand rng;

public:
	static void initDistribution(const std::string& text);

	generator(std::minstd_rand::result_type seed =
			std::minstd_rand::default_seed);

	void setSeed(std::minstd_rand::result_type seed =
			std::minstd_rand::default_seed);
	std::string::value_type getNextChar();
};

class generator2 {
private:
	static std::map<std::string::value_type, discrete_mapped_distribution<std::string::value_type>> letters;

	std::minstd_rand rng;

public:
	static void initDistribution(const std::string& text);

	generator2(std::minstd_rand::result_type seed =
			std::minstd_rand::default_seed);

	void setSeed(std::minstd_rand::result_type seed =
			std::minstd_rand::default_seed);
	std::string::value_type getNextChar(char in);
};
