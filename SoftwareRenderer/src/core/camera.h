#pragma once

#include <cmath>

#include "matrix.h"

class Camera
{
public:
	//inline Camera()
	//	: m_Resolution(vec2i(1, 1)), m_FOV(30), m_Far(100.0f), m_Near(0.1f)
	//{
	//}

	inline Camera(int resolutionW, int resolutionH, float fov, float farDist, float nearDist)
		: m_Resolution(vec2i(resolutionW, resolutionH)),
		m_FOV(fov), m_Far(farDist), m_Near(nearDist),
		m_ViewMatrixAvailable(false), m_ProjMatrixAvailable(false)
	{
	}

	inline Camera(vec2i resolution, float fov, float farDist, float nearDist)
		: m_Resolution(resolution),
		m_FOV(fov), m_Far(farDist), m_Near(nearDist),
		m_ViewMatrixAvailable(false), m_ProjMatrixAvailable(false)
	{
	}

	inline vec3 GetPosition() { return m_Position; }
	inline void SetPosition(vec3 pos) { m_Position = pos; m_ViewMatrixAvailable = false; }
	inline void Translate(vec3 v) { m_Position = m_Position + v; m_ViewMatrixAvailable = false; }

	mat4 GetViewMatrix();

	mat4 GetProjMatrix();
	vec4 Project(vec4 v);


private:
	vec3 m_Position;
	vec2i m_Resolution;
	float m_FOV, m_Far, m_Near;

	mat4 m_ViewMatrix;
	bool m_ViewMatrixAvailable;
	mat4 m_ProjMatrix;
	bool m_ProjMatrixAvailable;
};

