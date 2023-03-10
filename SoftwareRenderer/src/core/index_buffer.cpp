#include "index_buffer.h"

IndexBuffer::IndexBuffer() : m_Count(0)
{
	m_Indices = nullptr;
}

IndexBuffer::IndexBuffer(int count, int indices[]) : m_Count(count)
{
	if (count % 3)
	{
		count -= count % 3;
	}

	m_Indices = &indices[0];
}

IndexBuffer::~IndexBuffer()
{
	if (m_Indices) free(m_Indices);
}
