#pragma once

#include "basic.h"
#include "vector.h"

struct ColorRGB
{
	unsigned char r = 0, g = 0, b = 0;

	inline ColorRGB operator* (float operand)
	{
		return {
			(unsigned char)clamp(r * operand, 0, 255),
			(unsigned char)clamp(g * operand, 0, 255),
			(unsigned char)clamp(b * operand, 0, 255)
		};
	}

	inline ColorRGB operator* (vec3 operand)
	{
		return {
			(unsigned char)clamp(r * operand.x, 0, 255),
			(unsigned char)clamp(g * operand.y, 0, 255),
			(unsigned char)clamp(b * operand.z, 0, 255)
		};
	}
};