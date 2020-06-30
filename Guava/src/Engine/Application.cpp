#include "pch.h"

#include "Application.h"

#include "Core/Window.h"
#include "Core/Input.h"
#include "Core/ResourceManager.h"
#include "Core/StopWatch.h"
#include "Core/Log.h"

#include "Graphics/Renderer.h"

namespace Guava
{
	void GUI_Transform(Transform& t, bool child = false)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static vec3 position;
		static vec3 scale;
		static float rotation = 0;

		position = t.GetPosition();
		scale = t.GetScale();

		if (child) ImGui::BeginChild("Transform");
		else ImGui::Begin("Transform");

		if (ImGui::InputFloat3("Position",	&position[0], -5.f, 5.f))	t.SetPosition(position);
		if (ImGui::InputFloat3("Scale",		&scale[0], 0.1f, 5.f))		t.SetScale(scale);
		if (ImGui::SliderFloat("Y-Rotation",&rotation, 0.f, 360.f))		t.SetRotation(rotation, vec3(0, 1, 0));

		if (child) ImGui::EndChild();
		else ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	Application::Application(const string_view title)
	{
		// Logger init
		Logger::Create();

		// Window init
		Window::Create(title, 800, 600);
		Window::EnableVSync(true);

		// Input init
		Input::Create();

		// Renderer init
		Renderer::Create(RenderAPI::OpenGL);
		Renderer::SetFillMode(FillMode::Polygon);
		Renderer::SetClearColor(Color(0.3f, 0.3f, 0.8f));

		// Resources init
		ResourceManager::Create();

		// ImGUI init
		ImGui::CreateContext();
		ImGui::StyleColorsLight();
		ImGui_ImplGlfw_InitForOpenGL(Window::GetGLFW(), true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	Application::~Application()
	{
		// ImGUI shutdown
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// Resources shutdown
		ResourceManager::Destroy();

		// Renderer shutdown
		Renderer::Destroy();

		// Input shutdown
		Input::Destroy();

		// Window shutdown
		Window::Destroy();

		// Logger shutdown
		Logger::Destroy();
	}

	void Application::Run()
	{
		// Init quad
		ModelVertex v1, v2, v3, v4; {

			v1.Position = vec3(0, 0, 0);
			v1.Tangent = vec3(1, 0, 0);
			v1.Bitangent = vec3(0, 0, 1);
			v1.Normal =	vec3(0, 1, 0);
			v1.UV_Coords = vec2(0, 0);
			v4 = v3 = v2 = v1;

			v2.Position = vec3(1, 0, 0);
			v2.UV_Coords = vec2(1, 0);

			v3.Position = vec3(1, 0, 1);
			v3.UV_Coords = vec2(1, 1);

			v4.Position = vec3(0, 0, 1);
			v4.UV_Coords = vec2(0, 1);
		}
		vector<ModelVertex> vertices = { v1, v2, v3, v4 };
		vector<unsigned int> indices = {
			0, 1, 2,
			0, 2, 3
		};

		Material quadMaterial;
		quadMaterial.Albedo =	 Texture2D::LoadFromFile("assets/textures/brickwall.jpg");
		quadMaterial.NormalMap = Texture2D::LoadFromFile("assets/textures/brickwall_normal.jpg");

		Shader* meshShader = Shader::LoadFromName("mesh");

		Model* quad =	Model::LoadFromData(vertices, indices, &quadMaterial);
		Model* cyborg = Model::LoadFromFile("assets/models/cyborg/cyborg.obj");

		FreeFlyCamera	camera;
		StopWatch		timer;
		Transform		tQuad, tCyborg;
		double			dt = 0, dt_sum = 0;
		float			scale = 10.0f;

		tQuad.SetScale(scale);
		tQuad.SetPosition(-scale / 2.0f, 0.0f, -scale / 2.0f);

		camera.SetMoveSpeed(30.f);
		camera.SetRotationSpeed(0.2f);

		while (!Window::ShouldClose())
		{
			timer.Start();

			// Process input
			Input::Update(); {

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

				if (Input::MouseDown(MouseButton::RIGHT))
				{
					auto& mouseDelta = Input::GetMouseMovement();

					if (mouseDelta.x)
						camera.Yaw(-mouseDelta.x);

					if (mouseDelta.y)
						camera.Pitch(-mouseDelta.y);
				}
			}

			// Draw
			Renderer::ClearScreen();
			Renderer::BeginPass(meshShader, camera);
			Renderer::Draw(quad, tQuad);
			Renderer::Draw(cyborg, tCyborg);

			GUI_Transform(tCyborg);

			Window::Present();

			dt = timer.GetTime();
			dt_sum += dt;
		}
	}
}