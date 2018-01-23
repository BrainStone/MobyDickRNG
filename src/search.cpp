#include "search.hpp"

const std::string mobyDick = getMobyDick();
const size_t sizeMobyDick = mobyDick.size();

unsigned int calculateScore( std::function<uint8_t()> predicter ) {
	unsigned int score = 0;

	for ( size_t i = 0; i < (sizeMobyDick - 1); ) {
		if ( predicter() != mobyDick[++i] ) {
			++score;
		}
	}

	return score;
}

unsigned int calculateScore( std::function<uint8_t( uint8_t )> predicter ) {
	unsigned int score = 0;

	for ( size_t i = 0; i < (sizeMobyDick - 1); ) {
		if ( predicter( mobyDick[i] ) != mobyDick[++i] ) {
			++score;
		}
	}

	return score;
}

std::string getMobyDick() {
	// Open the Moby Dick file. 
	std::ifstream fileMobyDick( "resources/whale2.txt" );

	// Read the entire file
	std::string strMobyDick( (std::istreambuf_iterator<char>( fileMobyDick )), std::istreambuf_iterator<char>() );

	// Make sure there are no line breaks in the string
	std::remove_if( strMobyDick.begin(), strMobyDick.end(), []( char in ) { return in == '\r'; } );

	return strMobyDick;
}
