#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

class Window
{
public:
	Window(int width, int height, const wchar_t* title);
	~Window();

	void Draw(unsigned char const* framebuffer);
	void DispatchMsg();

private:
	HWND           m_Window;
	HDC            m_DC;
	unsigned char* m_FrameBuffer;

	int m_Width;
	int m_Height;
};