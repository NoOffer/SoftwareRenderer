#pragma once

#include <utility>
#include <time.h>

#include "core/core.h"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void Draw();
	unsigned char const* GetFrameBuffer();
private:
	void DrawLine(int x0, int y0, int x1, int y1, const ColorRGB& color);
	void DrawLine(vec2i x, vec2i y, const ColorRGB& color);

	vec3 FindBarycentric(vec2i& a, vec2i& b, vec2i& c, vec2i& p);
	void DrawTriangle(vec2i a, vec2i b, vec2i c, const ColorRGB& color);

	int m_Width, m_Height;
	unsigned char* m_FrameBuffer;

	int m_CurrentTimeMS;
	float m_DeltaTime;
};
