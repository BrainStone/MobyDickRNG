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
	std::string::const_reference oldLetter = *it++;

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

// TODO: Golf code!
