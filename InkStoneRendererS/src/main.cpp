#include <iostream>

#include "core\core.h"
#include "platforms\win32.h"

const int WIDTH = 500;
const int HEIGHT = 500;

int main()
{
	// Create renderer
	Renderer renderer(WIDTH, HEIGHT);

	// Window initialzation
	Window window(500, 500, L"Test Window");
	std::cout << "Window initialized." << std::endl;

	// Main loop
	while (1)
	{
		renderer.Draw();

		window.DispatchMsg();
		window.Draw(renderer.GetFrameBuffer());
	}
}