#include "lattice_noise.h"

lattice_noise::lattice_noise(unsigned noise_grid_resolution, unsigned seed, bool color) : noise_generator(seed, color)
{
	_noise_grid_resolution = noise_grid_resolution;
	_noise_grid = new float[_noise_grid_resolution * _noise_grid_resolution];

	calculate_noise_grid();
}

void lattice_noise::calculate_noise_grid()
{
	for (unsigned j = 0; j < _noise_grid_resolution; j++)
		for (unsigned i = 0; i < _noise_grid_resolution; i++)
			_noise_grid[get_array_index(_noise_grid_resolution, j, i)] = rand_01();
}

lattice_noise::~lattice_noise()
{
	delete[] _noise_grid;
}
