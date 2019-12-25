#include "pch.h"
#include "Guava/Core/Window.h"
#include "Guava/Core/Input.h"
#include "Guava/Core/StopWatch.h"
#include "Guava/Graphics/Renderer.h"
#include "Guava/Core/ResourceManager.h"

using namespace Guava;

int main()
{
	{
		Logger::Create();
		Window::Create("OpenGL Renderer", 800, 600);
		Input::Create();
		Renderer::Create(RenderAPI::OpenGL);

		Window::EnableVSync(true);
		Renderer::SetFillMode(FillMode::Polygon);
		Renderer::SetClearColor(Color(0.3f, 0.3f, 0.8f));

		// Load quad
		ModelVertex v1, v2, v3, v4;
		v1.Position = vec3(0, 0, 0);
		v1.Tangent = vec3(1, 0, 0);
		v1.Bitangent = vec3(0, 0, -1);
		v1.Normal = vec3(0, 1, 0);
		v1.UV_Coords = vec2(0, 0);
		v4 = v3 = v2 = v1;

		v2.Position = vec3(1, 0, 0);
		v2.UV_Coords = vec2(1, 0);

		v3.Position = vec3(1, 0, 1);
		v3.UV_Coords = vec2(1, 1);

		v4.Position = vec3(0, 0, 1);
		v4.UV_Coords = vec2(0, 1);

		vector<ModelVertex> vertices = {v1, v2, v3, v4};
		vector<unsigned int> indices = {
			0, 1, 2,
			0, 2, 3
		};

		Material mtl;
		mtl.Diffuse = Texture2D::LoadFromFile("assets/textures/missing.png");

		Model* quad = Model::LoadFromData(vertices, indices, &mtl);

		/* Load models*/
		u_set<string> ModelPaths = {
			"assets/models/nanosuit/nanosuit.obj",
			"assets/models/cyborg/cyborg.obj",
			"assets/models/planet/planet.obj",
			"assets/models/rock/rock.obj"
		};
		vector<Model*> Models(ModelPaths.size());
		time_point s = hr_clock::now();
		transform(GUAVA_EXECUTION_POLICY, ModelPaths.begin(), ModelPaths.end(), Models.begin(), [](const auto& path)
		{
			return Model::LoadFromFile(path);
		});
		duration d = hr_clock::now() - s;
		GUAVA_TRACE("Loading all models took {0} ms", std::chrono::duration_cast<std::chrono::milliseconds>(d).count());
		

		FreeFlyCamera		camera;
		StopWatch			timer;
		unsigned int		model = 0;
		double				numFrames = 0;
		double				dt = 0, dt_sum = 0;
		double				tInput = 0, tInputRender = 0;
		float				scale = 1.0f;
		size_t				n = 10;
		vector<Transform>	transforms(n * n);

		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j)
				transforms[n*i + j].SetPosition(i * scale, 0.0f, j * -scale);

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

			if(Input::KeyPress(Key::P))
				Renderer::SetFillMode(FillMode::Wireframe);
			else if(Input::KeyRelease(Key::P))
				Renderer::SetFillMode(FillMode::Polygon);

			if (Input::KeyPress(Key::UP))
				++model;
			else if (Input::KeyPress(Key::DOWN))
				--model;

			model = clamp((size_t)model, (size_t)0, Models.size() - 1);

			if (Input::MouseDown(MouseButton::RIGHT))
			{
				auto& mouseDelta = Input::GetMouseMovement();

				if (mouseDelta.x)
					camera.Yaw(-mouseDelta.x);

				if (mouseDelta.y)
					camera.Pitch(-mouseDelta.y);
			}

			//light.Position = camera.GetEyePosition();

			tInput += timer.GetTime();

			//std::for_each(GUAVA_EXECUTION_POLICY, transforms.begin(), transforms.end(), [&](Transform& t)
			//{
			//	t.Rotate(dt * 20.f, vec3(0.0f, 1.0f, 0.0f));
			//});

			// Draw
			Renderer::ClearScreen();
			Renderer::SetCamera(camera);
			Renderer::PointLight(vec3(0.0f, 15.0f, 0.0f), Color::White, 1.0f);
			Renderer::Draw(quad, transforms);
			Renderer::Draw(Models[model], transforms[(n / 2) * (n + 1)]);
			Renderer::RenderFrame();

			tInputRender += timer.GetTime();

			// This waits for vertical sync, don't include it in frame time
			Window::Present();

			numFrames++;

			dt = timer.GetTime();
			dt_sum += dt;
		}

		Renderer::Destroy();
		ResourceManager::Destroy();
		Input::Destroy();
		Window::Destroy();

		// Post stats
		auto fps = numFrames / dt_sum;
		auto tRender = (tInputRender - tInput) / numFrames;
		auto tFrame = tInputRender / numFrames;

		GUAVA_TRACE("Average stats");
		GUAVA_TRACE("FPS:         {0}", fps);
		GUAVA_TRACE("Render time: {0} ms", tRender * 1000.0);
		GUAVA_TRACE("Frame time:  {0} ms", tFrame * 1000.0);
	}

	//cin.get();
}
