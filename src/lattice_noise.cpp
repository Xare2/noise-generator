#include "lattice_noise.h"

lattice_noise::lattice_noise(unsigned noise_grid_resolution, unsigned seed, float frequency, bool color) : noise_generator(seed, color)
{
	m_frequency = frequency;

	m_noise_grid_resolution = noise_grid_resolution;
	this->calculate_noise_grid();
}

lattice_noise::~lattice_noise()
{
	delete[] m_noise_grid;
}

void lattice_noise::calculate_noise_grid()
{
	delete[] m_noise_grid;
	
	m_noise_grid = new float[m_noise_grid_resolution * m_noise_grid_resolution];

	for (unsigned j = 0; j < m_noise_grid_resolution; j++)
		for (unsigned i = 0; i < m_noise_grid_resolution; i++)
			m_noise_grid[get_array_index(m_noise_grid_resolution, j, i)] = rand_01();
}

void lattice_noise::set_frequency(float frequency)
{
	m_frequency = frequency;
}

void lattice_noise::set_seed(unsigned seed)
{
	noise_generator::set_seed(seed);

	this->calculate_noise_grid();
}
