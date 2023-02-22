#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	void Update();

private:
	HWND m_Window;
	HDC m_Dc;

	int m_Width;
	int m_Height;
};