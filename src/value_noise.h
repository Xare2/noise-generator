#pragma once
#include "lattice_noise.h"
class value_noise :
	public lattice_noise
{
private:
	float m_frequency;
	unsigned m_image_resolution;
	unsigned m_noise_mask;

public:
	value_noise(float frequency, unsigned image_resolution, unsigned noise_grid_resolution, unsigned seed, bool color);
	float eval(const float& x, const float& y);
};

