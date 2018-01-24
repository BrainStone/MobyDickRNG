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

// TODO: Golf code!
