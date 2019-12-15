#include "pch.h"
#include "Guava/Core/Window.h"
#include "Guava/Core/Input.h"
#include "Guava/Core/StopWatch.h"
#include "Guava/Core/AssetManager.h"
#include "Guava/Graphics/Renderer.h"

using namespace Guava;
using namespace std::chrono_literals;

int main()
{
	Logger::Create();
	Window::Create("OpenGL Renderer", 800, 600);
	Input::Create();
	Renderer::Create(RenderAPI::OpenGL);

	Window::EnableVSync(true);
	Renderer::SetDrawMode(PolygonMode::Fill);
	Renderer::SetClearColor(Color(0.4f, 0.4f, 0.9f, 1.0f));

	Shader*			meshShader = Shader::Create("mesh");
	Model*			nanosuit = Model::Create("nanosuit/nanosuit.obj");
	Model*			cyborg = Model::Create("cyborg/cyborg.obj");
	Light			light, lightBlue;
	FreeFlyCamera	camera(glm::vec3(), glm::vec3(0, 0, -1));
	Transform		nanoTransform, cyborgTransform;
	StopWatch		timer;
	double			numFrames = 0;
	double			dt = 0, dt_sum = 0;
	double			tInput = 0, tInputRender = 0;

	light.Position = { 24.0f, -10.0f, 6.0f, 1.0f};
	light.Color = Color::Red;
	light.Intensity = 0.6f;

	lightBlue.Position = { 24.0f, 10.0f, 6.0f, 1.0f };
	lightBlue.Color = Color::Blue;
	lightBlue.Intensity = 0.6f;

	nanoTransform.SetPosition(-5.f, 0.f, 0.f);
	nanoTransform.SetScale(1.0f);

	cyborgTransform.SetPosition(5.f, 0.f, 0.f);
	cyborgTransform.SetScale(4.0f);

	camera.SetMoveSpeed(30.f);
	camera.SetRotationSpeed(0.2f);

	while (!Window::ShouldClose())
	{
		timer.Start();

		// Process input
		Input::Update();

		if (Input::KeyDown(Key::W))
			camera.Move(0, 0, dt);
		if (Input::KeyDown(Key::S))
			camera.Move(0, 0, -dt);
		if (Input::KeyDown(Key::A))
			camera.Move(-dt, 0, 0);
		if (Input::KeyDown(Key::D))
			camera.Move(dt, 0, 0);
		if (Input::KeyDown(Key::SPACE))
			camera.Move(0, dt, 0);
		if (Input::KeyDown(Key::LEFT_CONTROL))
			camera.Move(0, -dt, 0);

		if (Input::KeyDown(Key::LEFT))
			light.Color = Color::Red;
		if (Input::KeyDown(Key::RIGHT))
			light.Color = Color::Blue;
		if (Input::KeyDown(Key::UP))
			light.Color = Color::White;
		if (Input::KeyDown(Key::DOWN))
			light.Color = Color::Green;

		if (Input::MouseDown(MouseButton::RIGHT))
		{
			auto& mouseDelta = Input::GetMouseMovement();

			if (mouseDelta.x)
				camera.Yaw(-mouseDelta.x);

			if (mouseDelta.y)
				camera.Pitch(-mouseDelta.y);
		}

		tInput += timer.GetTime();

		// Draw
		Renderer::ClearScreen();
		Renderer::Draw(light, meshShader);
		Renderer::Draw(lightBlue, meshShader);
		Renderer::Draw(nanosuit, meshShader, nanoTransform, camera);
		Renderer::Draw(cyborg, meshShader, cyborgTransform, camera);
		Renderer::RenderFrame();

		tInputRender += timer.GetTime();

		// This waits for vertical sync, so don't include it in frame time
		Window::Present();

		numFrames++;

		dt = timer.GetTime();
		dt_sum += dt;
	}

	AssetManager::Destroy();
	Renderer::Destroy();
	Input::Destroy();
	Window::Destroy();

	// Post stats
	auto fps = numFrames / dt_sum;
	auto tRender = (tInputRender - tInput) / numFrames;
	auto tFrame = tInputRender / numFrames;

	GUAVA_CORE_TRACE("Average stats");
	GUAVA_CORE_TRACE("FPS:         {0}", fps);
	GUAVA_CORE_TRACE("Render time: {0} ms", tRender * 1000.0);
	GUAVA_CORE_TRACE("Frame time:  {0} ms", tFrame * 1000.0);

	std::cin.get();
}
