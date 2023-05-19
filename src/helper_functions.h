// helper_funcions.h

#pragma once

template <typename T>
T get_array_index(T width, T row, T col)
{
	return row * width + col;;
}

float lerp(float v0, float v1, float t);
float smoothstep(float t);
float smoothstep(float v0, float v1, float t);
float smootherstep(float v0, float v1, float t);