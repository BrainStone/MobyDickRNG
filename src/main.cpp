#include "main.hpp"

std::atomic<std::minstd_rand::result_type> seed(0);

std::mutex bestScoreLock;
unsigned int bestScore = sizeMobyDick;
std::minstd_rand::result_type bestSeed = 0;
constexpr uint64_t limit = std::numeric_limits<uint32_t>::max();

int main() {
	const unsigned int cores = std::min( std::thread::hardware_concurrency(), 1U );
	const unsigned int threadsCount = cores * 10;
	std::minstd_rand::result_type currentSeed;
	unsigned int currentBestScore;
	std::minstd_rand::result_type currentBestSeed;
	std::list<std::thread> threads;

	generator::initDistribution( mobyDick );

	for ( unsigned int i = 0; i < threadsCount; ++i ) {
		threads.push_back( std::thread( search ) );
	}

	while ( seed < limit ) {
		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

		{
			std::lock_guard<std::mutex> lock( bestScoreLock );

			currentSeed = seed;
			currentBestScore = bestScore;
			currentBestSeed = bestSeed;
		}

		std::cout << "\rProgress: " << std::fixed << std::setprecision( 1 ) << ((double)currentSeed) / ((double)limit) * 100.0 << "% (" << currentSeed << '/' << limit << ") "
			"Best Seed: " << currentBestSeed << "   Best Score: " << currentBestScore << "            " << std::flush;
	}

	for ( std::thread& thread : threads ) {
		if ( thread.joinable() ) {
			thread.join();
		}
	}
}

void search() {
	unsigned int score;
	std::minstd_rand::result_type currentSeed;

	while ( seed < limit ) {
		currentSeed = seed++;
		generator gen( currentSeed );
		score = calculateScore( [&gen]() -> uint8_t { return gen.getNextChar(); } );

		{
			std::lock_guard<std::mutex> lock( bestScoreLock );

			if ( score < bestScore ) {
				bestScore = score;
				bestSeed = currentSeed;
			}
		}
	}
}
