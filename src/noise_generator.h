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
	int *m_image_data;
	unsigned m_seed;
	bool m_color;

protected:
	float rand_01();
	unsigned get_array_index(unsigned width, unsigned row, unsigned col);

public:
	noise_generator(unsigned s, bool color);
	~noise_generator();

	void set_color(bool color);
	
	virtual void set_seed(unsigned seed);
	virtual float eval(const float &x, const float &y);
};
