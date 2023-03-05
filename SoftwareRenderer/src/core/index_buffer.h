#pragma once

#include <windows.h>

class IndexBuffer
{
public:
	IndexBuffer(int count, float indices[]);
	~IndexBuffer();

	inline int GetCount() { return m_Count; }
	inline int operator[] (int i) { return m_Indices[i]; }

private:
	int m_Count;
	float* m_Indices;
};

