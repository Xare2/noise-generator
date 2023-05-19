#pragma once
#include "noise_generator.h"
class lattice_noise :
	public noise_generator
{
protected:
	float* _noise_grid;
	unsigned _noise_grid_resolution;


	void calculate_noise_grid();

public:
	/*point_noise(unsigned noise_grid_resolution = 256, unsigned seed = 0)
		: noise_generator(seed) { };*/
	lattice_noise(unsigned noise_grid_resolution, unsigned seed);
	~lattice_noise();
};

