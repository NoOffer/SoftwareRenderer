#pragma once

#include <Windows.h>
#include <cmath>
#include <utility>

#include "color.h"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void Draw();
	unsigned char const* GetFrameBuffer();
private:
	void DrawLine(int x0, int y0, int x1, int y1, ColorRGB color);

	int m_Width, m_Height;
	unsigned char* m_FrameBuffer;
};
