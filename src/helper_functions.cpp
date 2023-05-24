#include "helper_functions.h"

float lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}

float smoothstep(float t)
{
	return t * t * (3 - 2 * t);
}

float smoothstep(float v0, float v1, float t)
{
	return (v1 - v0) * (3.0f - t * 2.0f) * t * t + v0;
}

float smootherstep(float t)
{
    return (t * (t * 6.0f - 15.0f) + 10.0f) * t * t * t;
}

float smootherstep(float v0, float v1, float t)
{
	return (v1 - v0) * ((t * (t * 6.0f - 15.0f) + 10.0f) * t * t * t) + v0;
}