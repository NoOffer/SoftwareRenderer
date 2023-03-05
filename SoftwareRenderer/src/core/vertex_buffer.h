#pragma once

#include "vector.h"

class VertexBuffer
{
public:
	VertexBuffer(int count, vec3 vertices[]);
	~VertexBuffer();

	inline vec4 operator[](int i) { return m_Vertices[i]; }
	inline int GetCount() { return m_Count; }

private:
	vec4* m_Vertices;
	int m_Count;
};

