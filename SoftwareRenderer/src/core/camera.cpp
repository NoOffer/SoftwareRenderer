#include "camera.h"

// Retrun: X' valid in [-W', W'], Y' valid in [-W', W'], Z' valid in [0, 1], W' = Z
mat4 Camera::GetProjMatrix()
{
	mat4 m_ProjMatrix;

	float n = 1 / (2 * std::tan(m_FOV / 2));
	m_ProjMatrix[0][0] = n * m_Resolution.y / m_Resolution.x;
	m_ProjMatrix[0][2] = 0.5f;
	m_ProjMatrix[1][1] = n;
	m_ProjMatrix[1][2] = 0.5f;
	m_ProjMatrix[2][2] = 1 / (m_Far - m_Near);
	m_ProjMatrix[2][3] = -m_Near / (m_Far - m_Near);
	m_ProjMatrix[3][2] = 1;

	return m_ProjMatrix;
}

vec3 Camera::Project(vec3 v)
{
	float n = (2 * std::tan(m_FOV * 11 / 1260)) * v.z;

	v.x = (v.x / (n / m_Resolution.y * m_Resolution.x) + 0.5f) * m_Resolution.x;
	v.y = (v.y / n + 0.5f) * m_Resolution.y;
	v.z = (v.z - m_Near) / (m_Far - m_Near);

	return v;
}