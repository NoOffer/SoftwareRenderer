#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(int count, vec3 vertices[]) : m_Count(count)
{
	if (count % 3)
	{
		count -= count % 3;
	}

	m_Vertices = (vec4*)malloc(sizeof(vec4) * count);
	
	if (m_Vertices)
	{
		for (int i = 0; i < count; i++)
		{
			m_Vertices[i] = vec4(vertices[i], 1.0f);
		}
	}
}

VertexBuffer::~VertexBuffer()
{
	if(m_Vertices) free(m_Vertices);
}