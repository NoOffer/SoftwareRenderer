#include "vertex_buffer.h"

VertexBuffer::VertexBuffer() : m_Count(0)
{
	m_Vertices = nullptr;
}

VertexBuffer::VertexBuffer(int count, vec3 vertices[]) : m_Count(count)
{
	m_Vertices = &vertices[0];
}

VertexBuffer::~VertexBuffer()
{
	if(m_Vertices) free(m_Vertices);
}