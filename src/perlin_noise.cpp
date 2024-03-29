#include "perlin_noise.h"

perlin_noise::perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color)
	: lattice_noise(noise_grid_resolution, seed, frequency, color)
{
	printf("Create perlin noise\n");
	this->create_vector_grid();
	this->calculate_image_data();
}

perlin_noise::~perlin_noise()
{
	delete[] m_vector_grid;
}

void perlin_noise::create_vector_grid()
{
	delete[] m_vector_grid;

	m_vector_grid = new vector2[m_noise_grid_resolution * m_noise_grid_resolution];

	for (unsigned j = 0; j < m_noise_grid_resolution; j++)
		for (unsigned i = 0; i < m_noise_grid_resolution; i++)
		{
			float random = rand_01() * 2 * M_PI;

			vector2 v;
			v.x = cos(random);
			v.y = sin(random);

			m_vector_grid[get_array_index(m_noise_grid_resolution, j, i)] = v;
		}
}

float perlin_noise::dot_grid_gradient(unsigned ix, unsigned iy, float x, float y)
{
	vector2 gradient = m_vector_grid[get_array_index(m_noise_grid_resolution, iy, ix)];

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx * gradient.x + dy * gradient.y);
}

void perlin_noise::set_seed(unsigned seed)
{
	lattice_noise::set_seed(seed);

	this->create_vector_grid();
	this->calculate_image_data();
}

void perlin_noise::set_resolution(unsigned resolution)
{
	lattice_noise::set_resolution(resolution);

	this->create_vector_grid();
	this->calculate_image_data();
}

float perlin_noise::eval(const float &x, const float &y)
{
	float px = x * m_frequency;
	float py = y * m_frequency;

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

	n0 = this->dot_grid_gradient(x0, y0, px, py);
	n1 = this->dot_grid_gradient(x1, y0, px, py);
	ix0 = smootherstep(n0, n1, sx);

	n0 = this->dot_grid_gradient(x0, y1, px, py);
	n1 = this->dot_grid_gradient(x1, y1, px, py);
	ix1 = smootherstep(n0, n1, sx);

	value = smootherstep(ix0, ix1, sy);
	return value * .5f + .5f;
}