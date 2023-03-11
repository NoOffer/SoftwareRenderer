#include "index_buffer.h"

IndexBuffer::IndexBuffer(int count, int indices[]) : m_Count(count)
{
	if (count % 3)
	{
		count -= count % 3;
	}


	m_Indices = (int*)malloc(sizeof(int) * count);
	if (m_Indices) for (int i = 0; i < count; i++)
	{
		m_Indices[i] = indices[i] - 1;
	}
}

IndexBuffer::~IndexBuffer()
{
	if (m_Indices) free(m_Indices);
}
