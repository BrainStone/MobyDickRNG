//#define GOLFED

#ifdef GOLFED

// TODO!

#else // GOLFED

#include "generator.hpp"

std::discrete_distribution<size_t> generator::distr;
std::vector<std::string::value_type> generator::letters;

void generator::initDistribution( const std::string& text ) {
	typedef std::map<std::string::value_type, uint64_t> distributionMap;

	distributionMap letterDistribution;

	for ( std::string::const_reference letter : text ) {
		++letterDistribution[letter];
	}

	generator::letters = std::vector<std::string::value_type>();
	std::vector<uint64_t> counts = std::vector<uint64_t>();

	generator::letters.reserve( letterDistribution.size() );
	counts.reserve( letterDistribution.size() );

	for ( distributionMap::const_reference count : letterDistribution ) {
		generator::letters.push_back( count.first );
		counts.push_back( count.second );
	}

	generator::distr = std::discrete_distribution<size_t>( counts.cbegin(), counts.cend() );
}

generator::generator( std::minstd_rand::result_type seed ) :
	rng( seed ) {}

std::string::value_type generator::getNextChar() {
	return letters.at( distr( rng ) );
}

#endif // !GOLFED
