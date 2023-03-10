#pragma once

#include <windows.h>

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(int count, int indices[]);
	~IndexBuffer();

	inline int GetCount() { return m_Count; }
	inline int operator[] (int i) { return m_Indices[i]; }

private:
	int m_Count;
	int* m_Indices;
};

