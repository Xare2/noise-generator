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
	unsigned m_seed;
	bool m_color;

protected:
	float rand_01();
	unsigned get_array_index(unsigned width, unsigned row, unsigned col);

public:
	noise_generator(unsigned s, bool color);

	virtual float eval(const float &x, const float &y);
	virtual int *getImageArray(unsigned width, unsigned height);
};
