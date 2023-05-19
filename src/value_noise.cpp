#include "value_noise.h"

value_noise::value_noise(float frequency, unsigned image_resolution, unsigned noise_grid_resolution, unsigned seed, bool color)
	: lattice_noise(noise_grid_resolution, seed, color)
{
	_frequency = frequency;
	_image_resolution = image_resolution;
	_noise_mask = noise_grid_resolution - 1;
}

float value_noise::eval(const float & x, const float & y)
{
	float px = x * _frequency;
	float py = y * _frequency;

	int xi = static_cast<int>(std::floor(px));
	int yi = static_cast<int>(std::floor(py));

	float tx = px - xi;
	float ty = py - yi;

	int rx0 = xi & _noise_mask;
	int rx1 = (rx0 + 1) & _noise_mask;
	int ry0 = yi & _noise_mask;
	int ry1 = (ry0 + 1) & _noise_mask;

	const float & c00 = _noise_grid[ry0 * _noise_mask + rx0];
	const float & c10 = _noise_grid[ry0 * _noise_mask + rx1];
	const float & c01 = _noise_grid[ry1 * _noise_mask + rx0];
	const float & c11 = _noise_grid[ry1 * _noise_mask + rx1];

	// remapping of tx and ty using the Smoothstep function 
	float sx = smoothstep(tx);
	float sy = smoothstep(ty);

	// linearly interpolate values along the x axis
	float nx0 = lerp(c00, c10, sx);
	float nx1 = lerp(c01, c11, sx);

	return lerp(nx0, nx1, sy);
}
