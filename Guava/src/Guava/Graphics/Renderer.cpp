#include "pch.h"
#include "Renderer.h"
#include "Model.h"
#include "OpenGL/glRenderer.h"
#include "Guava/Core/Window.h"

namespace Guava
{
	// API
	static RenderAPI s_RenderAPI;

	// Instance
	static std::unique_ptr<Renderer> s_Instance;

	// Projection
	static glm::mat4 s_Perspective;

	// Lights
	static int s_NumLights = 0;
	constexpr int s_MaxLights = 100;
	static std::string s_LightUniformArray;

	Renderer::~Renderer()
	{
		
	}

	void Renderer::Create(RenderAPI api)
	{
		Destroy();

		s_RenderAPI = api;

		switch (api)
		{
			case RenderAPI::OpenGL: 
			{
				s_Instance.reset(new OpenGL::glRenderer());
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
		s_Instance.reset();
	}

	void Renderer::ClearScreen()
	{
		s_Instance->ClearScreen_Impl();
	}

	void Renderer::RenderFrame()
	{
		s_NumLights = 0;
	}

	void Renderer::SetClearColor(const Color& color)
	{
		s_Instance->SetClearColor_Impl(color);
	}

	void Renderer::SetWindowSize(const glm::uvec2& size)
	{
		auto winSize = Window::GetSize();
		SetViewport(winSize);
		s_Perspective = glm::perspective(glm::radians(70.f), (float)winSize.x / (float)winSize.y, 0.1f, 1000.f);
	}

	void Renderer::Draw(const Model* model, Shader* shader, Transform& transform, Camera& camera)
	{
		shader->Bind();

		shader->SetMat4("u_modelMatrix", transform.GetTransform());
		shader->SetMat3("u_normalMatrix", transform.GetNormalTransform());
		shader->SetMat4("u_viewMatrix", camera.GetViewMatrix());
		shader->SetMat4("u_projectionMatrix", s_Perspective);
		shader->SetVec4("u_eyePos", { camera.GetEyePosition(), 1.0f });
		shader->SetInt("u_diffuse", 0);

		model->Draw();
	}

	void Renderer::Draw(const Light& light, Shader* shader)
	{
		if (s_NumLights < s_MaxLights - 1)
		{
			s_LightUniformArray = "u_lights[" + std::to_string(s_NumLights) + "].";

			shader->Bind();
			shader->SetVec4(s_LightUniformArray + "position_world", light.Position);
			shader->SetVec4(s_LightUniformArray + "color", light.Color);
			shader->SetFloat(s_LightUniformArray + "intensity", light.Intensity);

			s_NumLights++;
			shader->SetInt("u_numLights", s_NumLights);
		}
	}

	Texture* Renderer::CreateTexture(const StringView file, const TextureCreationInfo& info)
	{
		switch (s_RenderAPI)
		{
			case RenderAPI::OpenGL:
			{
				return new OpenGL::glTexture(file, info);
			}
			default:
			{
				GUAVA_ASSERT(false, "Unknown render-API specified. Texture was not created");
			}
		}
	}

	Model* Renderer::CreateModel(const StringView filePath)
	{
		switch (s_RenderAPI)
		{
			case RenderAPI::OpenGL:
			{
				return new OpenGL::glModel(filePath);
			}
			default:
			{
				GUAVA_ASSERT(false, "Unknown render-API specified. Model was not created");
			}
		}
	}

	Shader* Renderer::CreateShader(const StringView name)
	{
		switch (s_RenderAPI)
		{
			case RenderAPI::OpenGL:
			{
				return new OpenGL::glShader(name);
			}
			default:
			{
				GUAVA_ASSERT(false, "Unknown render-API specified. Shader was not created");
			}
		}
	}
	
	void Renderer::SetViewport(const glm::uvec2& size, const glm::uvec2& bottomLeft)
	{
		s_Instance->SetViewport_Impl(size, bottomLeft);
	}

	void Renderer::SetDrawMode(const PolygonMode polyMode)
	{
		s_Instance->SetDrawMode_Impl(polyMode);
	}

	Renderer::Renderer()
	{
	}
}
