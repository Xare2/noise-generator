#include "perlin_noise.h"

perlin_noise::perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed) : lattice_noise(noise_grid_resolution, seed)
{
	_frequency = frequency;
	_vector_grid = new vector2[noise_grid_resolution * noise_grid_resolution];

	for (unsigned j = 0; j < noise_grid_resolution; j++)
		for (unsigned i = 0; i < noise_grid_resolution; i++)
		{
			float random = rand_01() * 2 * M_PI;

			vector2 v;
			v.x = cos(random); v.y = sin(random);

			_vector_grid[get_array_index(noise_grid_resolution, j, i)] = v;
		}
}

float perlin_noise::dotGridGradient(unsigned ix, unsigned iy, float x, float y)
{
	vector2 gradient = _vector_grid[get_array_index(_noise_grid_resolution, iy, ix)];

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx*gradient.x + dy * gradient.y);
}

float perlin_noise::eval(const float & x, const float & y)
{
	float px = x * _frequency;
	float py = y * _frequency;
	
	unsigned x0 = (unsigned)floor(px);
	unsigned x1 = x0 + 1;
	unsigned y0 = (unsigned)floor(py);
	unsigned y1 = y0 + 1;

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = px - (float)x0;
	float sy = py - (float)y0;

	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;

	n0 = this->dotGridGradient(x0, y0, px, py);
	n1 = this->dotGridGradient(x1, y0, px, py);
	ix0 = smootherstep(n0, n1, sx);
								 
	n0 = this->dotGridGradient(x0, y1, px, py);
	n1 = this->dotGridGradient(x1, y1, px, py);
	ix1 = smootherstep(n0, n1, sx);

	value = smootherstep(ix0, ix1, sy);
	return value * .5f + .5f; 
}