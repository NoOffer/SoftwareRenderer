#include "Renderer.h"

Renderer::Renderer(int width, int height) : m_Width(width), m_Height(height)
{
	m_FrameBuffer = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 3);
	if (m_FrameBuffer) memset(m_FrameBuffer, 0, sizeof(unsigned char) * width * height * 3);
}

Renderer::~Renderer()
{
	free(m_FrameBuffer);
}

void Renderer::Draw()
{
	DrawLine(500, 500, 300, 0, { 255, 80, 20 });
}

unsigned char const* Renderer::GetFrameBuffer()
{
	return (unsigned char const*)m_FrameBuffer;
}

void Renderer::DrawLine(int x0, int y0, int x1, int y1, ColorRGB color)
{
	// Temporary confinement
	x0 = min(max(x0, 0), m_Width);
	y0 = min(max(y0, 0), m_Height);
	x1 = min(max(x1, 0), m_Width);
	y1 = min(max(y1, 0), m_Height);

	int dx = std::abs(x0 - x1);
	int dy = std::abs(y0 - y1);
	bool steep = false;
	if (dy > dx)
	{
		// Ensure X as main
		std::swap(x0, y0);
		std::swap(x1, y1);
		std::swap(dx, dy);
		steep = true;
	}

	int error = 0;
	if (x0 > x1)
	{
		// Ensure left−to−right 
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int j = y0;
	for (int i = x0; i <= x1; i++)
	{
		int idx;
		if (steep)
		{
			idx = (i * m_Width + j) * 3;
		}
		else
		{
			idx = (j * m_Width + i) * 3;
		}
		m_FrameBuffer[idx] = color.r;
		m_FrameBuffer[idx + 1] = color.g;
		m_FrameBuffer[idx + 2] = color.b;

		error += dy * 2;
		if (error > dx)
		{
			j += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}