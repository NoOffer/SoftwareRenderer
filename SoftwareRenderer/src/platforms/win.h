#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <vector>
//#include <iostream>

class Window
{
public:
	Window(int width, int height, const wchar_t* title);
	~Window();

	bool IsAlive();
	void Draw(unsigned char const* framebuffer);
	void DispatchMsg();

private:
	HWND           m_Window;
	HDC            m_DC;
	unsigned char* m_FrameBuffer;

	//std::vector<HWND> m_UIElements;

	int m_Width;
	int m_Height;

	//void SetupUI();
};