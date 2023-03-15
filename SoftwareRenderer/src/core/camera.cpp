#include "camera.h"

#include <iostream>

mat4 Camera::GetViewMatrix()
{
	if (!m_ViewMatrixAvailable)
	{
		vec3 z = normalize(vec3(0.0f, 0.0f, 0.0f) - m_Position);
		vec3 x = normalize(cross(vec3(0.0f, 1.0f, 0.0f), z));
		vec3 y = normalize(cross(z, x));

		mat4 Minv(1.0f);
		mat4 Tr(1.0f);

		Minv[0][0] = x.x;
		Minv[0][1] = x.y;
		Minv[0][2] = x.z;
		Minv[1][0] = y.x;
		Minv[1][1] = y.y;
		Minv[1][2] = y.z;
		Minv[2][0] = z.x;
		Minv[2][1] = z.y;
		Minv[2][2] = z.z;
		//Minv[0][3] = m_Position.x;
		//Minv[1][3] = m_Position.y;
		//Minv[2][3] = m_Position.z;
		Tr[0][3] = -m_Position.x;
		Tr[1][3] = -m_Position.y;
		Tr[2][3] = -m_Position.z;

		m_ViewMatrix = mul(Minv, Tr);
		//m_ViewMatrix = Minv;

		m_ViewMatrixAvailable = true;
	}

	return m_ViewMatrix;
}

// Retrun: X' valid in [0, viewport.x], Y' valid in [0, viewport.y], W' = Z
mat4 Camera::GetProjMatrix()
{
	if (!m_ProjMatrixAvailable)
	{
		m_ProjMatrix = mat4(0.0f);

		float n = m_Resolution.y / (2 * std::tan(m_FOV * 11 / 1260));
		m_ProjMatrix[0][0] = n;
		m_ProjMatrix[0][2] = 0.5f * m_Resolution.x;
		m_ProjMatrix[1][1] = n;
		m_ProjMatrix[1][2] = 0.5f * m_Resolution.y;

		//// Tranditional, Z' valid in [-W', W']
		//m_ProjMatrix[2][2] = m_Far / (m_Far - m_Near);
		//m_ProjMatrix[2][3] = m_Far * m_Near / (m_Far - m_Near);
		
		// Experimental, Z' valid in [0, 1]
		m_ProjMatrix[2][2] = 1 / (m_Far - m_Near);
		m_ProjMatrix[2][3] = m_Near / (m_Near - m_Far);

		m_ProjMatrix[3][2] = 1.0f;

		m_ProjMatrixAvailable = true;
	}

	return m_ProjMatrix;
}

vec4 Camera::Project(vec4 v)
{
	float n = (2 * std::tan(m_FOV * 11 / 1260)) * std::abs(v.z);

	v.x = (v.x / (n / m_Resolution.y * m_Resolution.x) + 0.5f) * m_Resolution.x;
	v.y = (v.y / n + 0.5f) * m_Resolution.y;
	v.z = (v.z - m_Near) / (m_Far - m_Near);

	return v;
}