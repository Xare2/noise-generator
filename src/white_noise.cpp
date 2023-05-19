#include "white_noise.h"

float white_noise::eval(const float & x, const float & y)
{
	unsigned i = (int)x % _noise_grid_resolution;
	unsigned j = (int)y % _noise_grid_resolution;


	return _noise_grid[get_array_index(_noise_grid_resolution, j, i)];
}
