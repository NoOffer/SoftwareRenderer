#pragma once

#include <Windows.h>

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void Draw();
	unsigned char const* GetFrameBuffer();
private:
	int m_Width, m_Height;
	unsigned char* m_Framebuffer;
};
