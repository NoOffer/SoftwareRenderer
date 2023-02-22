#include "Renderer.h"

Renderer::Renderer(int width, int height) : m_Width(width), m_Height(height)
{
	m_Framebuffer = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 3);
	if (m_Framebuffer) memset(m_Framebuffer, 0, sizeof(unsigned char) * width * height * 3);
}

Renderer::~Renderer()
{
	free(m_Framebuffer);
}

void Renderer::Draw()
{
	for (int i = 0; i < 500; i++)
	{
		m_Framebuffer[(i * m_Width + i) * 3 + 2] = (unsigned char)200;
	}
}

unsigned char const* Renderer::GetFrameBuffer()
{
	return (unsigned char const*)m_Framebuffer;
}