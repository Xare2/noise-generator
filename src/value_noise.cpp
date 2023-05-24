#include "value_noise.h"

value_noise::value_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color)
	: lattice_noise(noise_grid_resolution, seed, frequency, color)
{
}

float value_noise::eval(const float &x, const float &y)
{
	float px = x * m_frequency;
	float py = y * m_frequency;

	unsigned xi = static_cast<unsigned>(std::floor(px));
	unsigned yi = static_cast<unsigned>(std::floor(py));

	float tx = px - xi;
	float ty = py - yi;

	unsigned rx0 = xi % m_noise_grid_resolution;
	unsigned rx1 = (rx0 + 1) % m_noise_grid_resolution;
	unsigned ry0 = yi % m_noise_grid_resolution;
	unsigned ry1 = (ry0 + 1) % m_noise_grid_resolution;

	const float &c00 = m_noise_grid[ry0 * m_noise_grid_resolution + rx0];
	const float &c10 = m_noise_grid[ry0 * m_noise_grid_resolution + rx1];
	const float &c01 = m_noise_grid[ry1 * m_noise_grid_resolution + rx0];
	const float &c11 = m_noise_grid[ry1 * m_noise_grid_resolution + rx1];

	// remapping of tx and ty using the Smoothstep function
	float sx = smootherstep(tx);
	float sy = smootherstep(ty);

	// linearly interpolate values along the x axis
	float nx0 = lerp(c00, c10, sx);
	float nx1 = lerp(c01, c11, sx);

	return lerp(nx0, nx1, sy);
}
