#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(int count, vec3 vertices[]) : m_Count(count)
{
	m_Vertices = (vec3*)malloc(sizeof(vec3) * count);
	
	if (m_Vertices)
	{
		for (int i = 0; i < count; i++)
		{
			m_Vertices[i] = vertices[i];
		}
	}
}

VertexBuffer::~VertexBuffer()
{
	if(m_Vertices) free(m_Vertices);
}