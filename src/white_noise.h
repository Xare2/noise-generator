#pragma once
#include "lattice_noise.h"
class white_noise :
	public lattice_noise
{
public:
	float eval(const float& x, const float& y);
};

