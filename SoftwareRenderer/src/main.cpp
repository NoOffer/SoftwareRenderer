#include <iostream>

#include "core\core.h"
#include "renderer.h"
#include "platforms\win.h"

const int WIDTH = 500;
const int HEIGHT = 300;

int main()
{
	// Create camera
	Camera cam((int)WIDTH, (int)HEIGHT, 30, 100.0f, 0.1f);
	cam.SetPosition(vec3(0.0f, 2.0f, -15.0f));
	// Create renderer
	Renderer renderer(WIDTH, HEIGHT, &cam);

	// Window initialzation
	Window window((int)WIDTH, (int)HEIGHT, L"Test Window");
	std::cout << "Window initialized." << std::endl;

	std::vector<Model*> models;
	ObjParser::Parse("res/test_cube_model.obj", models);
	//ObjParser::Parse("res/test_sphere_model.obj", models);

	Model testModel(
		"Test Model",
		4,
		new vec3[4] {
			vec3(-10.0f, -1.0f, -10.0f),
			vec3( 10.0f, -1.0f, -10.0f),
			vec3( 10.0f, -1.0f,  10.0f),
			vec3(-10.0f, -1.0f,  10.0f) },
		6,
		new int[6] { 1, 2, 3, 1, 3, 4 });

	// Main loop
	float t = 1;
	while (window.IsAlive())
	{
		renderer.ClearBuffer();

		for (Model* model : models)
		{
			renderer.Draw(*model);
		}
		renderer.Draw(testModel);

		window.DispatchMsg();
		window.Draw(renderer.GetFrameBuffer());

		cam.SetPosition(vec3(std::cos(t) * 20.0f, 3.0f, std::sin(t) * 20.0f));
		t += 0.01f;
	}
}