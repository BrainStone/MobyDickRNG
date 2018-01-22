#pragma once

#include <map>
#include <random>
#include <string>
#include <vector>

class generator {
private:
	static std::discrete_distribution<size_t> distr;
	static std::vector<std::string::value_type> letters;

	std::minstd_rand rng;

public:
	static void initDistribution( const std::string& text );

	generator( std::minstd_rand::result_type seed );

	std::string::value_type getNextChar();
};
