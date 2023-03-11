#include <iostream>

#include "core\core.h"
#include "renderer.h"
#include "platforms\win32.h"

const int WIDTH = 500;
const int HEIGHT = 500;

int main()
{
	// Create camera
	Camera cam((int)WIDTH, (int)HEIGHT, 60, 100.0f, 0.1f);
	cam.SetPosition(vec3(1.0f, 0.0f, -5.0f));
	// Create renderer
	Renderer renderer(WIDTH, HEIGHT, &cam);

	// Window initialzation
	Window window(500, 500, L"Test Window");
	std::cout << "Window initialized." << std::endl;

	std::vector<Model*> models;
	ObjParser::Parse("res/test_model.obj", models);

	//Model testModel(
	//	"Test Model",
	//	3,
	//	new vec3[3] { vec3(-1.0f, -1.0f, 10.0f), vec3(1.0f, -1.0f, 10.0f), vec3(0.0f, 1.0f, 20.0f) },
	//	3,
	//	new int[3] { 0, 1, 2 });

	// Main loop
	float t = 0;
	while (window.IsAlive())
	{
		renderer.ClearBuffer();

		//renderer.Draw(testModel);
		for (Model* model : models)
		{
			renderer.Draw(*model);
		}

		window.DispatchMsg();
		window.Draw(renderer.GetFrameBuffer());

		cam.SetPosition(vec3(std::cos(t) * 5.0f, 1.0f, std::sin(t) * 5.0f));
		t += 0.01f;
	}
}