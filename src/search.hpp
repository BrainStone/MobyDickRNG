#pragma once

#include <algorithm>
#include <functional>
#include <fstream>
#include <string>

#undef max
#undef min

extern const std::string mobyDick;
extern const size_t sizeMobyDick;

unsigned int calculateScore( std::function<uint8_t()> predicter );
unsigned int calculateScore( std::function<uint8_t( uint8_t )> predicter );
std::string getMobyDick();
