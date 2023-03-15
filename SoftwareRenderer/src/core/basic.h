#pragma once

#include <windows.h>

inline float clamp(float t, float minVal, float maxVal)
{
	return max(min(t, maxVal), minVal);
}