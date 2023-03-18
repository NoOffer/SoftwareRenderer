#pragma once

#include <windows.h>
#include <iostream>

#define Log(x) std::cout << x << std::endl;

inline float clamp(float t, float minVal, float maxVal)
{
	return max(min(t, maxVal), minVal);
}