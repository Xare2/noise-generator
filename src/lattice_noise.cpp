#include "lattice_noise.h"

lattice_noise::lattice_noise(unsigned noise_grid_resolution, unsigned seed, bool color) : noise_generator(seed, color)
{
	m_noise_grid_resolution = noise_grid_resolution;
	m_noise_grid = new float[m_noise_grid_resolution * m_noise_grid_resolution];

	calculate_noise_grid();
}

void lattice_noise::calculate_noise_grid()
{
	for (unsigned j = 0; j < m_noise_grid_resolution; j++)
		for (unsigned i = 0; i < m_noise_grid_resolution; i++)
			m_noise_grid[get_array_index(m_noise_grid_resolution, j, i)] = rand_01();
}

lattice_noise::~lattice_noise()
{
	delete[] m_noise_grid;
}
