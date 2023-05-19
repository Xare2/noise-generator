#pragma once

#include "helper_functions.h"
#include <cstdlib>
#include <cmath>

struct vector2
{
	float x, y;
};

class noise_generator
{
private:
	unsigned _seed;
	bool _color;

protected:
	float rand_01();

public:
	noise_generator(unsigned s = 0, bool color = false);

	virtual float eval(const float &x, const float &y);
	virtual int* getImageArray(unsigned width, unsigned height);
};
