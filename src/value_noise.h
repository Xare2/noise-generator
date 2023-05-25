#pragma once
#include "lattice_noise.h"
class value_noise : public lattice_noise
{
private:
public:
	value_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);

	float eval(const float &x, const float &y) override;
};
