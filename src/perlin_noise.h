#pragma once
#include "lattice_noise.h"
#define _USE_MATH_DEFINES
#include <math.h>


class perlin_noise :
	public lattice_noise
{
private:
	float m_frequency;
	vector2* m_vector_grid;

	float dotGridGradient(unsigned ix, unsigned iy, float x, float y);

public:
	perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
	~perlin_noise();
	float eval(const float& x, const float& y);
};

