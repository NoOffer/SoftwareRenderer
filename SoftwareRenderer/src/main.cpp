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
	ObjParser::Parse("res/models/simple-test-models/test_cube_model.obj", models);
	//ObjParser::Parse("res/test_sphere_model.obj", models);

	Model testModel(
		"Test Model",
		4,
		new vec3[4]{
			vec3(-10.0f, -1.0f, -10.0f),
			vec3(10.0f, -1.0f, -10.0f),
			vec3(10.0f, -1.0f,  10.0f),
			vec3(-10.0f, -1.0f,  10.0f) },
			6,
			new int[6] { 1, 2, 3, 1, 3, 4 });

	// Main loop
	float t = 0.0f, h = 3.0f;
	bool paused = false;
	while (window.IsAlive())
	{
		window.DispatchMsg();

		// Handle inputs
		{
			std::unordered_map<UINT, KeyState>& keyStates = window.GetKeyStates();
			if (keyStates[KEY_SPACE] == KeyState::Pressed) { paused = !paused; }

			if (paused) { continue; }

			double deltaTime = renderer.GetDeltaTime() + 0.001;
			if (keyStates[KEY_W] <= KeyState::Released) { h += 15.0f * deltaTime; }
			if (keyStates[KEY_S] <= KeyState::Released) { h -= 15.0f * deltaTime; }
			if (keyStates[KEY_A] <= KeyState::Released) { t -= 1.5f * deltaTime; }
			if (keyStates[KEY_D] <= KeyState::Released) { t += 1.5f * deltaTime; }
		}

		renderer.ClearBuffer();

		for (Model* model : models)
		{
			renderer.Draw(*model);
		}
		renderer.Draw(testModel);

		window.Draw(renderer.GetFrameBuffer());

		cam.SetPosition(vec3(std::cos(t) * 20.0f, h, std::sin(t) * 20.0f));
	}
}