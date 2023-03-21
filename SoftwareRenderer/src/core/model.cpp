#include "model.h"

Model::Model(const char* name, int vertCount, vec3* vertices, int idxCount, int* indices)
	: m_Name(name), m_VB(VertexBuffer(vertCount, vertices)), m_IB(IndexBuffer(idxCount, indices))
{
}

Model::~Model() {}
