#include "noise_generator.h"

noise_generator::noise_generator(unsigned s, bool color)
{
	m_seed = s;
	m_color = color;
	m_image_data = nullptr;

	std::srand(m_seed);
}

noise_generator::~noise_generator()
{
	delete[] m_image_data;
}

float noise_generator::rand_01()
{
	return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

unsigned noise_generator::get_array_index(unsigned width, unsigned row, unsigned col)
{
	return row * width + col;
}

float noise_generator::eval(const float &x, const float &y)
{
	return -1;
}

int *noise_generator::getImageArray(unsigned width, unsigned height)
{
	// A Uint8ClampedArray representing a one-dimensional array containing the data in the RGBA order
	// The Uint8ClampedArray contains height × width × 4 bytes of data

	m_image_data = new int[width * height * 4];
	const unsigned size = width * height;

	for (float i = 0; i < width; i++)
		for (float j = 0; j < height; j++)
		{
			const unsigned idx = get_array_index(width * 4, j * 4, i);

			const unsigned r_idx = idx + 0;
			const unsigned g_idx = idx + 1;
			const unsigned b_idx = idx + 2;
			const unsigned a_idx = idx + 3;

			// TODO color

			float n = eval(i, j);

			m_image_data[r_idx] = n * 255;
			m_image_data[g_idx] = n * 255;
			m_image_data[b_idx] = n * 255;
			m_image_data[a_idx] = 255;
		}

	return m_image_data;
}