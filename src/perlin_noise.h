#pragma once
#include "lattice_noise.h"
#define _USE_MATH_DEFINES
#include <math.h>

class perlin_noise : public lattice_noise
{
private:
	vector2 *m_vector_grid;

	void create_vector_grid();
	float dot_grid_gradient(unsigned ix, unsigned iy, float x, float y);
	// void

public:
	perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
	~perlin_noise();

	void set_seed(unsigned seed) override;
	void set_resolution(unsigned resolution) override;
	float eval(const float &x, const float &y) override;
};
