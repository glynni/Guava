#include "pch.h"
#include "Renderer.h"
#include "Model.h"
#include "OpenGL/glRenderer.h"
#include "Engine/Core/Window.h"

namespace Guava
{
	static RenderAPI API;
	static scope<Renderer> Instance;

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

	void Renderer::ClearDepth()
	{
		Instance->ClearDepth_Impl();
	}

	void Renderer::SetClearColor(const Color& color)
	{
		Instance->SetClearColor_Impl(color);
	}

	void Renderer::SetWindowSize(const uvec2& size)
	{
		SetViewport(size);

		if (size.y > 0)
			Instance->m_Projection = perspective(radians(70.f), (float)size.x / (float)size.y, 0.1f, 1000.f);
	}

	void Renderer::BeginPass(Shader* shader, Camera& camera)
	{
		if (!shader) return;

		Instance->m_CurrentShader = shader;

		shader->Bind();
		shader->SetVec3("u_ambientLight", vec3(0.0f));
		shader->SetVec3("u_eyePos", camera.GetEyePosition());

		shader->SetMat4("u_viewMatrix", camera.GetViewMatrix());
		shader->SetMat4("u_projectionMatrix", Instance->m_Projection);
	}

	void Renderer::Draw(Model* model, Transform& transform)
	{
		static vector<ModelInstance> instance(1);

		instance[0].ModelMatrix = transform.GetMatrix();

		model->Draw(Instance->m_CurrentShader, instance);
	}

	void Renderer::Draw(Model* model, vector<Transform>& transforms)
	{
		static vector<ModelInstance> instances;

		instances.resize(transforms.size());

		std::transform(GUAVA_EXECUTION_POLICY, transforms.begin(), transforms.end(), instances.begin(), [](Transform& t) -> ModelInstance
		{
			return { t.GetMatrix() };
		});

		model->Draw(Instance->m_CurrentShader, instances);
	}
	
	void Renderer::SetViewport(const uvec2& size, const uvec2& bottomLeft)
	{
		Instance->SetViewport_Impl(size, bottomLeft);
	}

	void Renderer::SetFillMode(const FillMode polyMode)
	{
		Instance->SetDrawMode_Impl(polyMode);
	}

	Model* Renderer::CreateModel()
	{
		return Instance->CreateModel_Impl();
	}

	Texture2D* Renderer::CreateTexture2D(const Texture2DCreateInfo& tci)
	{
		return Instance->CreateTexture2D_Impl(tci);
	}

	Shader* Renderer::CreateShader()
	{
		return Instance->CreateShader_Impl();
	}
}
