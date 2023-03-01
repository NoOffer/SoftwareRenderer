#pragma once

#include <Windows.h>

inline float clamp(float t, float minVal, float maxVal)
{
	return max(min(t, maxVal), minVal);
}