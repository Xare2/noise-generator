#pragma once

#include "helper_functions.h"
#include <cstdlib>

struct vector2
{
	float x, y;
};


class noise_generator
{
private:
	unsigned _seed;
	float rand_01();

public:
	noise_generator(unsigned s = 0);

	virtual float eval(const float& x, const float& y);
};

