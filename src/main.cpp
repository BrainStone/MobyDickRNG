#include "main.hpp"

int main() {
	generator::initDistribution( mobyDick );

	for ( std::minstd_rand::result_type i = 0; i < 10; ++i ) {
		generator gen( i );

		std::cout << "i = " << i << " -> " << calculateScore( [&gen]() -> uint8_t { return gen.getNextChar(); } ) << std::endl;
	}
}
