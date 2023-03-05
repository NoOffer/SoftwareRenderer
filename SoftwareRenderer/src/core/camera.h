#pragma once

#include <cmath>

#include "matrix.h"

class Camera
{
public:
	inline Camera()
		: m_Resolution(vec2i(1, 1)), m_FOV(30), m_Far(100.0f), m_Near(0.1f)
	{
	}

	inline Camera(vec2i resolution, float fov, float farDist, float nearDist)
		: m_Resolution(resolution), m_FOV(fov), m_Far(farDist), m_Near(nearDist)
	{
	}

	mat4 GetProjMatrix();

private:
	vec2i m_Resolution;
	float m_FOV, m_Far, m_Near;

	mat4 m_ProjMatrix;
};

