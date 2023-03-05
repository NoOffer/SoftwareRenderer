#include "matrix.h"

mat4::mat4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_Mat[i][j] = 0.0f;
		}
	}
}

mat4::mat4(float a)
{
	mat4();
	m_Mat[0][0] = a;
	m_Mat[1][1] = a;
	m_Mat[2][2] = a;
	m_Mat[3][3] = a;
}

mat4 mat4::Transpose()
{
	mat4 res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res[i][j] = m_Mat[j][i];
		}
	}
	
	return res;
}

vec4 mul(mat4 mat, vec4 vec)
{
	vec4 res;
	res.x = mat[0][0] * vec.x + mat[0][1] * vec.y + mat[0][2] * vec.z + mat[0][3] * vec.w;
	res.y = mat[1][0] * vec.x + mat[1][1] * vec.y + mat[1][2] * vec.z + mat[1][3] * vec.w;
	res.z = mat[2][0] * vec.x + mat[2][1] * vec.y + mat[2][2] * vec.z + mat[2][3] * vec.w;
	res.w = mat[3][0] * vec.x + mat[3][1] * vec.y + mat[3][2] * vec.z + mat[3][3] * vec.w;
	return res;
}