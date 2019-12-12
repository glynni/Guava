#include "pch.h"
#include "Guava/Core/Window.h"
#include "Guava/Core/Input.h"
#include "Guava/Graphics/Renderer.h"

using namespace Guava;
using namespace std::chrono_literals;

int main()
{
	Logger::Create();
	Window::Create("OpenGL Renderer", 800, 600);
	Input::Create();
	Renderer::Create(RenderAPI::OpenGL);
	Renderer::SetDrawMode(PolygonMode::Fill);
	Renderer::SetClearColor(ColorRGBA(0.4f, 0.4f, 0.9f, 1.0f));

	Shader*		meshShader = Shader::Create("mesh");
	Shader*		spriteShader = Shader::Create("sprite");
	//Model*	hammer = Model::Create("hammer/source/Warhammer.fbx");
	Model*		pbrChart = Model::Create("pbr-chart.obj");
	Light		redLight;
	Camera		camera;
	Transform	tHammer, tPbr;

	std::chrono::high_resolution_clock::time_point	start;
	std::chrono::duration<float>					frameTime = 0s;

	redLight.Position = { 24.0f, -10.0f, 6.0f };
	redLight.Color = { 1.0f, 0.3f, 0.3f, 1.0f };
	redLight.Intensity = 1.0f;

	camera.SetPosition({0.0f, 0.0f, 0.0f});
	camera.SetMoveSpeed(50.0f);

	tHammer.SetPosition({ 0.0f, -10.f, -10.f });
	tHammer.SetScale({ 0.3f, 0.3f, 0.3f });
	tHammer.SetRotation(0.0f, { 0.0f, 0.0f, 1.0f });

	while (!Window::ShouldClose())
	{
		start = std::chrono::high_resolution_clock::now();

		// Process input
		Input::Update();

		if (Input::KeyDown(Key::W))
			camera.MoveForwards();
		if (Input::KeyDown(Key::S))
			camera.MoveBackwards();
		if (Input::KeyDown(Key::A))
			camera.MoveLeft();
		if (Input::KeyDown(Key::D))
			camera.MoveRight();
		if (Input::KeyDown(Key::SPACE))
			camera.MoveUpwards();
		if (Input::KeyDown(Key::LEFT_CONTROL))
			camera.MoveDownWards();

		if (Input::MouseDown(MouseButton::RIGHT))
		{
			auto& mouseDelta = Input::GetMouseMovement();

			camera.Yaw(-mouseDelta.x);
			camera.Pitch(-mouseDelta.y);
		}

		// Update
		float dt = frameTime.count();
		camera.Update(dt);
		tHammer.Rotate(dt * 10.f);

		// Draw
		Renderer::BeginFrame();
		Renderer::Draw(redLight);
		Renderer::Draw(pbrChart, meshShader, tPbr, camera);
		Renderer::EndFrame();

		frameTime = std::chrono::high_resolution_clock::now() - start;
	}

	Renderer::Destroy();
	Input::Destroy();
	Window::Destroy();

	//std::cin.get();
}
