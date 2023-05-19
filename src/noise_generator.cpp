#include "noise_generator.h"

noise_generator::noise_generator(unsigned s, bool color)
{
	_seed = s;
	_color = color;
	std::srand(_seed);
}

float noise_generator::rand_01()
{
	return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

float noise_generator::eval(const float &x, const float &y)
{
	return -1;
}

int *noise_generator::getImageArray(unsigned width, unsigned height)
{
	// The Uint8ClampedArray contains height × width × 4 bytes of data

	int *imageData = new int[width * height * 4];

	for (float i = 0; i < width; i++)
		for (float j = 0; j < height; j++)
		{

		}

	return nullptr;
}