#include "white_noise.h"

float white_noise::eval(const float & x, const float & y)
{
	unsigned i = (int)x % m_noise_grid_resolution;
	unsigned j = (int)y % m_noise_grid_resolution;


	return m_noise_grid[get_array_index(m_noise_grid_resolution, j, i)];
}
