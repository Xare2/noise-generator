#pragma once

#include "helper_functions.h"
#include <cstdlib>
#include <cstdio>
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

	static const int MAX_RESOLUTION = 4096;
	unsigned m_image_resolution;

	float rand_01();
	unsigned get_array_index(unsigned width, unsigned row, unsigned col);

public:
	int* image_data; // i don't like this being public but i can't find any other way to retrive data from js

	noise_generator(unsigned resolution, unsigned seed, bool color);
	~noise_generator();
	void calculate_image_data();
	void populate_image_data(int* image);

	void proba_array(int* array, int size);

	void set_color(bool color);

	virtual void set_seed(unsigned seed);
	virtual float eval(const float &x, const float &y);
};
