#include "voronoi_noise.h"

voronoi_noise::voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed) :
	noise_generator(seed)
{
	_image_resolution = image_resolution;
	_cell_amount = cell_amount;

	_cell_grid = new vector2[_cell_amount];

	for (unsigned i = 0; i < _cell_amount; i++)
	{
		vector2 v;
		v.x = rand_01();
		v.y = rand_01();

		_cell_grid[i] = v;
	}
}

float voronoi_noise::distance(vector2 a, vector2 b)
{
	return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

float voronoi_noise::eval(const float & x, const float & y)
{
	vector2 point;
	point.x = x / (float)_image_resolution;
	point.y = y / (float)_image_resolution;
	
	float distance = INFINITY;
	
	for (unsigned i = 0; i < _cell_amount; i++)
	{
		vector2 v = _cell_grid[i];

		float d = this->distance(v, point);

		if (d < distance)
			distance = d;
	}

	return std::fmin(distance * 2, 1.f);
}