#include "voronoi_noise.h"

voronoi_noise::voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed, bool color)
	: noise_generator(seed, color)
{
	m_image_resolution = image_resolution;
	m_cell_amount = cell_amount;

	this->create_cell_grid();
}

voronoi_noise::~voronoi_noise()
{
	delete[] m_cell_grid;
}

void voronoi_noise::create_cell_grid()
{
	delete[] m_cell_grid;
	m_cell_grid = new vector2[m_cell_amount];

	for (unsigned i = 0; i < m_cell_amount; i++)
	{
		vector2 v;
		v.x = rand_01();
		v.y = rand_01();

		m_cell_grid[i] = v;
	}
}

float voronoi_noise::distance(vector2 a, vector2 b)
{
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void voronoi_noise::set_cell_amount(unsigned cell_amount)
{
	m_cell_amount = cell_amount;
	this->create_cell_grid();
}

void voronoi_noise::set_seed(unsigned seed)
{
	noise_generator::set_seed(seed);
	this->create_cell_grid();
}

// TODO store array with distances to change F1, F2, F3, etc...
float voronoi_noise::eval(const float &x, const float &y)
{
	vector2 point;
	point.x = x / (float)m_image_resolution;
	point.y = y / (float)m_image_resolution;

	float distance = INFINITY;

	for (unsigned i = 0; i < m_cell_amount; i++)
	{
		vector2 v = m_cell_grid[i];

		float d = this->distance(v, point);

		if (d < distance)
			distance = d;
	}

	return std::fmin(distance * 2, 1.f);
}