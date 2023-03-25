#pragma once

#include "matrix.h"


class Light
{
public:

private:
	mat4 m_ViewMatrix;
	bool m_ViewMatrixAvailable;
	mat4 m_ProjMatrix;
	bool m_ProjMatrixAvailable;
};

