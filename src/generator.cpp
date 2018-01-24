#include "generator.hpp"

discrete_mapped_distribution<std::string::value_type> generator::letters;

void generator::initDistribution(const std::string& text) {
	std::map<std::string::value_type, uint64_t> letterDistribution;

	for (std::string::const_reference letter : text) {
		++letterDistribution[letter];
	}

	generator::letters = discrete_mapped_distribution<std::string::value_type>(letterDistribution);
}

generator::generator(std::minstd_rand::result_type seed) :
		rng(seed) {
}

void generator::setSeed(std::minstd_rand::result_type seed) {
	rng.seed(seed);
}

std::string::value_type generator::getNextChar() {
	return letters(rng);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::map<std::string::value_type, discrete_mapped_distribution<std::string::value_type>> generator2::letters;

void generator2::initDistribution(const std::string& text) {
	std::map<std::string::value_type, std::map<std::string::value_type, uint64_t>> letterDistribution;

	std::string::const_iterator it = text.cbegin();
	std::string::value_type oldLetter = *it++;

	for (; it != text.cend();) {
		++(letterDistribution[oldLetter][*it]);
		oldLetter = *it++;
	}

	generator2::letters = std::map<std::string::value_type, discrete_mapped_distribution<std::string::value_type>>();

	for(std::map<std::string::value_type, std::map<std::string::value_type, uint64_t>>::const_reference letter : letterDistribution) {
		generator2::letters[letter.first] = discrete_mapped_distribution<std::string::value_type>(letter.second);
	}
}

generator2::generator2(std::minstd_rand::result_type seed) :
		rng(seed) {
}

void generator2::setSeed(std::minstd_rand::result_type seed) {
	rng.seed(seed);
}

std::string::value_type generator2::getNextChar(char in) {
	return letters.at(in)(rng);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO: Golf code!

#if FALSE

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

std::map<std::string::value_type, discrete_mapped_distribution<std::string::value_type>> generator2::letters;

void generator2::initDistribution(const std::string& text) {
	std::map<std::string::value_type, std::map<std::string::value_type, uint64_t>> letterDistribution;

	std::string::const_iterator it = text.cbegin();
	std::string::value_type oldLetter = *it++;

	for (; it != text.cend();) {
		++(letterDistribution[oldLetter][*it]);
		oldLetter = *it++;
	}

	generator2::letters = std::map<std::string::value_type, discrete_mapped_distribution<std::string::value_type>>();

	for(std::map<std::string::value_type, std::map<std::string::value_type, uint64_t>>::const_reference letter : letterDistribution) {
		generator2::letters[letter.first] = discrete_mapped_distribution<std::string::value_type>(letter.second);
	}
}

generator2::generator2(std::minstd_rand::result_type seed) :
		rng(seed) {
}

void generator2::setSeed(std::minstd_rand::result_type seed) {
	rng.seed(seed);
}

std::string::value_type generator2::getNextChar(char in) {
	return letters.at(in)(rng);
}

#endif
