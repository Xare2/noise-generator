#pragma once
#include "noise_generator.h"
class lattice_noise :
	public noise_generator
{
protected:
	float* m_noise_grid;
	float m_frequency;
	unsigned m_noise_grid_resolution;


	void calculate_noise_grid();

public:
	/*point_noise(unsigned noise_grid_resolution = 256, unsigned seed = 0)
		: noise_generator(seed) { };*/
	lattice_noise(unsigned noise_grid_resolution, unsigned seed, float frequency, bool color);
	~lattice_noise();

	void set_frequency(float frequency);
	virtual void set_resolution(unsigned resolution);

	void set_seed(unsigned seed) override;
};

