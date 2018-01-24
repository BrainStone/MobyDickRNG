#pragma once

#include <algorithm>
#include <functional>
#include <fstream>
#include <string>

#undef max
#undef min

unsigned int calculateScore( std::function<uint8_t()> predicter );
unsigned int calculateScore( std::function<uint8_t( uint8_t )> predicter );
std::string getMobyDick();

const std::string mobyDick(getMobyDick());
const size_t sizeMobyDick(mobyDick.size());
