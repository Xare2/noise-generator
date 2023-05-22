#pragma once
#include "noise_generator.h"
class voronoi_noise :
	public noise_generator
{
private:
	vector2* m_cell_grid;
	unsigned m_cell_amount;
	unsigned m_image_resolution;

	float distance(vector2 a, vector2 b);

public:
	voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed, bool color);
	float eval(const float& x, const float& y);
};

