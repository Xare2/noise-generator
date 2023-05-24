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

void noise_generator::set_seed(unsigned seed)
{
	m_seed = seed;
}

void noise_generator::set_color(bool color)
{
	m_color = color;
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