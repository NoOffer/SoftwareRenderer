#include "index_buffer.h"

IndexBuffer::IndexBuffer(int count, float indices[]) : m_Count(count)
{
	if (count % 3)
	{
		count -= count % 3;
	}

	m_Indices = (float*)malloc(sizeof(float) * count);

	if (m_Indices)
	{
		for (int i = 0; i < count; i++)
		{
			m_Indices[i] = indices[i];
		}
	}
}

IndexBuffer::~IndexBuffer()
{
	if (m_Indices) free(m_Indices);
}
