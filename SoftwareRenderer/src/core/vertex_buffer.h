#pragma once

#include "vector.h"

class VertexBuffer
{
public:
	VertexBuffer(int count, vec3 vertices[]);
	~VertexBuffer();

	inline vec3 operator[](int i) { return m_Vertices[i]; }
	inline int GetCount() { return m_Count; }

private:
	int m_Count;
	vec3* m_Vertices;
};

