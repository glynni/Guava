#include "pch.h"
#include "Renderer.h"
#include "Model.h"
#include "OpenGL/glRenderer.h"
#include "Guava/Core/Window.h"

namespace Guava
{
	// API
	static RenderAPI API;

	// Instance
	static scope<Renderer> Instance;

	// Camera
	static mat4 Perspective;

	// Lights
	static int NumLights = 0;

	void Renderer::Create(RenderAPI api)
	{
		Destroy();

		API = api;

		switch (api)
		{
			case RenderAPI::OpenGL: 
			{
				Instance.reset(new OpenGL::glRenderer());
				break;
			}
			default:
			{
				GUAVA_ASSERT(false, "Unknown render-API specified. Renderer was not created");
				break;
			}
		}

		SetWindowSize(Window::GetSize());
	}

	void Renderer::Destroy()
	{
		Instance.reset();
	}

	void Renderer::ClearScreen()
	{
		Instance->ClearScreen_Impl();
	}

	void Renderer::RenderFrame()
	{
		NumLights = 0;
	}

	void Renderer::SetClearColor(const Color& color)
	{
		Instance->SetClearColor_Impl(color);
	}

	void Renderer::SetWindowSize(const uvec2& size)
	{
		SetViewport(size);

		if (size.y > 0)
			Perspective = perspective(radians(70.f), (float)size.x / (float)size.y, 0.1f, 1000.f);
	}

	void Renderer::Draw(Model* model, Transform& transform)
	{
		static Shader* shader = Shader::LoadFromFiles("mesh_vertex.glsl", "mesh_fragment.glsl");
		static vector<ModelInstance> instance(1);

		instance[0].ModelMatrix = transform.GetTransform();

		shader->Bind();

		model->Draw(shader, instance);
	}

	void Renderer::Draw(Model* model, vector<Transform>& transforms)
	{
		static Shader* shader = Shader::LoadFromFiles("mesh_vertex.glsl", "mesh_fragment.glsl");
		static vector<ModelInstance> instances;

		instances.resize(transforms.size());

		std::transform(GUAVA_EXECUTION_POLICY, transforms.begin(), transforms.end(), instances.begin(), [](Transform& t) -> ModelInstance
		{
			return { t.GetTransform() };
		});

		shader->Bind();

		model->Draw(shader, instances);
	}

	void Renderer::PointLight(const vec3& lightPos, const Color& lightColor, const float intensity)
	{
		static constexpr unsigned int numMaxLights = 10;
		static Shader* shader = Shader::LoadFromFiles("mesh_vertex.glsl", "mesh_fragment.glsl");
		static string uniform, arrayPos; // avoid string reallocations

		if (NumLights < numMaxLights - 1)
		{
			arrayPos = "u_lights[" + std::to_string(NumLights) + "].";

			shader->Bind();

			uniform = arrayPos + "position";
			shader->SetVec3(uniform, lightPos);

			uniform = arrayPos + "color";
			shader->SetVec3(uniform, vec3(lightColor));

			uniform = arrayPos + "intensity";
			shader->SetFloat(uniform, intensity);

			NumLights++;
			shader->SetInt("u_numLights", NumLights);
		}
	}
	
	void Renderer::SetViewport(const uvec2& size, const uvec2& bottomLeft)
	{
		Instance->SetViewport_Impl(size, bottomLeft);
	}

	void Renderer::SetFillMode(const FillMode polyMode)
	{
		Instance->SetDrawMode_Impl(polyMode);
	}

	void Renderer::SetCamera(Camera& camera)
	{
		static Shader* shader = Shader::LoadFromFiles("mesh_vertex.glsl", "mesh_fragment.glsl");

		shader->Bind();
		shader->SetMat4("u_viewMatrix", camera.GetViewMatrix());
		shader->SetMat4("u_projectionMatrix", Perspective);
		shader->SetVec3("u_eyePos", camera.GetEyePosition());
	}

	Model* Renderer::CreateModel()
	{
		return Instance->CreateModel_Impl();
	}

	Texture2D* Renderer::CreateTexture(const Texture2DCreateInfo& tci)
	{
		return Instance->CreateTexture_Impl(tci);
	}

	Shader* Renderer::CreateShader()
	{
		return Instance->CreateShader_Impl();
	}
}
