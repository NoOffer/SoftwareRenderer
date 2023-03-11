#pragma once

#include <Windows.h>

class IndexBuffer
{
public:
	IndexBuffer(int count, int indices[]);
	~IndexBuffer();

	inline int GetCount() { return m_Count; }
	inline int operator[] (int i) { return m_Indices[i]; }

private:
	int m_Count;
	int* m_Indices;
};

