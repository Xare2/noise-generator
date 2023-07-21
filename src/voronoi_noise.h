#pragma once
#include "noise_generator.h"
class voronoi_noise :
	public noise_generator
{
private:
	vector2* m_cell_grid;
	unsigned m_cell_amount;

	void create_cell_grid();
	float distance(vector2 a, vector2 b);

public:
	voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed, bool color);
	~voronoi_noise();
	
	void set_cell_amount(unsigned cell_amount);
	void set_resolution(unsigned resolution);

	void set_seed(unsigned seed) override;
	float eval(const float& x, const float& y) override;
};

