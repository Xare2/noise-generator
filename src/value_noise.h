#pragma once
#include "lattice_noise.h"
class value_noise :
	public lattice_noise
{
private:
	float _frequency;
	unsigned _image_resolution;
	unsigned _noise_mask;

public:
	value_noise(float frequency = 1, unsigned image_resolution = 512, unsigned noise_grid_resolution = 256, unsigned seed = 0);
	float eval(const float& x, const float& y);
};

