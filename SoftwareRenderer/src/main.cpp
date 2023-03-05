#include <iostream>

#include "core\core.h"
#include "renderer.h"
#include "platforms\win32.h"

const int WIDTH = 500;
const int HEIGHT = 500;

int main()
{
	// Create camera
	Camera cam((int)WIDTH, (int)HEIGHT, 30, 100.0f, 0.1f);
	// Create renderer
	Renderer renderer(WIDTH, HEIGHT, cam);

	// Window initialzation
	Window window(500, 500, L"Test Window");
	std::cout << "Window initialized." << std::endl;

	// Vertex buffer
	VertexBuffer vb(3, new vec3[3]{ vec3(10, 10, 50), vec3(400, 100, 80), vec3(100, 400, 80) });
	IndexBuffer ib(3, new float[3]{ 0, 1, 2 });

	// Main loop
	while (window.IsAlive())
	{
		renderer.Draw(vb, ib);

		window.DispatchMsg();
		window.Draw(renderer.GetFrameBuffer());
	}
}