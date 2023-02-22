#include <iostream>

#include "platforms\win32.h"

const int WIDTH = 500;
const int HEIGHT = 500;

int main()
{
	unsigned char* framebuffer = (unsigned char*)malloc(sizeof(unsigned char) * WIDTH * HEIGHT * 3);
	if (framebuffer) memset(framebuffer, 0, sizeof(unsigned char) * WIDTH * HEIGHT * 3);

	Window window(500, 500, L"Test Window");
	std::cout << "Window initialized." << std::endl;
	std::cout << GetSystemMetrics(SM_CXFRAME) << " " << GetSystemMetrics(SM_CYFRAME) << " " << GetSystemMetrics(SM_CXSIZE) << std::endl;

	while (1)
	{
		for (int i = 0; i < 500; i++)
		{
			framebuffer[(i * WIDTH + i) * 3] = (unsigned char)200;
		}
		window.Draw(framebuffer);
		window.DispatchMsg();
	}

	free(framebuffer);
}