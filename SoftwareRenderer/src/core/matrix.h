#pragma once

#include "vector.h"

struct mat4
{
	// Top-left: [0, 0], top-right: [0, 3]
	float m_Mat[4][4];

	mat4();

	mat4(float a);

	inline float* operator[](int i)
	{
		return m_Mat[i];
	}

	mat4 Transpose();
};

vec4 mul(mat4& mat, vec4 vec);

mat4 mul(mat4& m1, mat4& m2);