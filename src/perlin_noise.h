#pragma once
#include "lattice_noise.h"
#define _USE_MATH_DEFINES
#include <math.h>


class perlin_noise :
	public lattice_noise
{
private:
	float _frequency;
	vector2* _vector_grid;

	float dotGridGradient(unsigned ix, unsigned iy, float x, float y);

public:
	perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
	float eval(const float& x, const float& y);
};

