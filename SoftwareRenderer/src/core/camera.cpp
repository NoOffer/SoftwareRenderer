#include "camera.h"

// Retrun: X' valid in [-W', W'], Y' valid in [-W', W'], Z' valid in [0, 1], W' = Z
mat4 Camera::GetProjMatrix(){
	mat4 m_ProjMatrix;

	float cotTheta = 1 / std::tan(m_FOV / 2);
	m_ProjMatrix[0][0] = cotTheta * m_Resolution.y / m_Resolution.x;
	m_ProjMatrix[1][1] = cotTheta;
	m_ProjMatrix[2][2] = 1 / (m_Far - m_Near);
	m_ProjMatrix[2][3] = -m_Near / (m_Far - m_Near);
	m_ProjMatrix[3][2] = 1;

	return m_ProjMatrix;
}