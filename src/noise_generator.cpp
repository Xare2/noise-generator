#include "noise_generator.h"

noise_generator::noise_generator(unsigned s)
{
	_seed = s;
	std::srand(_seed);
}

float noise_generator::eval(const float & x, const float & y) 
{
	return -1;
}

float noise_generator::rand_01()
{
	return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
}