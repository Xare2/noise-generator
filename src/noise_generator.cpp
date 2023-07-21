#include "noise_generator.h"

noise_generator::noise_generator(unsigned resolution, unsigned seed, bool color)
{
	m_seed = seed;
	m_color = color;
	m_image_resolution = resolution;

	std::srand(m_seed);
	printf("noise module created\n");
}

noise_generator::~noise_generator()
{
	delete[] image_data;
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

void noise_generator::calculate_image_data()
{
	delete[] image_data;

	image_data = new int[m_image_resolution * m_image_resolution * 4];

	unsigned idx = 0;
	for (unsigned i = 0; i < m_image_resolution; i++)
		for (unsigned j = 0; j < m_image_resolution; j++)
		{
			float c = this->eval(i, j);

			image_data[idx + 0] = (c * 255);
			image_data[idx + 1] = (c * 255);
			image_data[idx + 2] = (c * 255);
			image_data[idx + 3] = (255);

			idx += 4;
		}

	

	printf("image created with resolution %d and size %d\n", m_image_resolution, idx);
}

void noise_generator::populate_image_data(int *image)
{
	unsigned idx = 0;
	for (unsigned i = 0; i < m_image_resolution; i++)
		for (unsigned j = 0; j < m_image_resolution; j++)
		{
			float c = this->eval(i, j);

			image_data[idx + 0] = (c * 255);
			image_data[idx + 1] = (c * 255);
			image_data[idx + 2] = (c * 255);
			image_data[idx + 3] = (255);

			idx += 4;
		}
}

void noise_generator::proba_array(int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		array[i] += 5;
	}
}

unsigned noise_generator::get_array_index(unsigned width, unsigned row, unsigned col)
{
	return row * width + col;
}

float noise_generator::eval(const float &x, const float &y)
{
	return -1;
}