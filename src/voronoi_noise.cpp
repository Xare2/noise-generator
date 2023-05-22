#include "voronoi_noise.h"

voronoi_noise::voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed, bool color) :
	noise_generator(seed, color)
{
	m_image_resolution = image_resolution;
	m_cell_amount = cell_amount;

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
	return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

float voronoi_noise::eval(const float & x, const float & y)
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