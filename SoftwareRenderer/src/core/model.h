#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"

#include <iostream>

class Model
{
public:
	Model(const char* name, int vertCount, vec3* vertices, int idxCount, int* indices);
	~Model();

	inline VertexBuffer& GetVertexBuffer() { return m_VB; }
	inline IndexBuffer& GetIndexBuffer() { return m_IB; }

private:
	const char* m_Name;
	VertexBuffer m_VB;
	IndexBuffer m_IB;
};

