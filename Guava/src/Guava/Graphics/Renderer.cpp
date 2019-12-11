#include "pch.h"
#include "Guava/Core/Window.h"
#include "OpenGL/glRenderer.h"
#include "OpenGL/glTexture.h"
#include "OpenGL/glMesh.h"
#include "Guava/Core/AssetManager.h"

namespace Guava
{
	// API
	RenderAPI s_RenderAPI;

	// Instance
	std::unique_ptr<Renderer> s_Instance;

	// Projection
	glm::mat4 s_Perspective;

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
		AssetManager::ClearAssets();
		s_Instance.reset();
	}

	void Renderer::ClearScreen()
	{
		s_Instance->ClearScreen_Impl();
	}

	void Renderer::BeginFrame()
	{
		ClearScreen();
	}

	void Renderer::EndFrame()
	{
		Window::Present();
	}

	void Renderer::SetClearColor(const Color& color)
	{
		s_Instance->SetClearColor_Impl(color);
	}

	void Renderer::SetWindowSize(const glm::uvec2& size)
	{
		auto winSize = Window::GetSize();
		SetViewport(winSize);
		s_Perspective = glm::perspective(glm::radians(70.f), (float)winSize.x / (float)winSize.y, 0.1f, 100.f);
	}

	void Renderer::Draw(Mesh* mesh, Shader* shader, const Transform& transform, const Camera& camera)
	{
		shader->Bind();

		shader->SetMat4("u_ModelMatrix", transform.GetTransform());
		shader->SetMat4("u_ViewMatrix", camera.GetViewMatrix());
		shader->SetMat4("u_ProjectionMatrix", s_Perspective);
		shader->SetVec4("u_EyePos", { camera.GetPosition() , 1.0f});

		mesh->Draw();
	}

	Texture* Renderer::CreateTexture(const std::string_view file, const Texture::Description& description)
	{
		switch (s_RenderAPI)
		{
			case RenderAPI::OpenGL:
			{
				return new OpenGL::glTexture(description, file);
			}
			default:
			{
				GUAVA_ASSERT(false, "Unknown render-API specified. Texture was not created");
			}
		}
	}

	Mesh* Renderer::CreateMesh(const aiMesh* mesh)
	{
		switch (s_RenderAPI)
		{
			case RenderAPI::OpenGL:
			{
				return new OpenGL::glMesh(mesh);
			}
			default:
			{
				GUAVA_ASSERT(false, "Unknown render-API specified. Mesh was not created");
			}
		}
	}

	Shader* Renderer::CreateShader(const std::string_view name)
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

	void Renderer::SetDrawMode(const PolygonMode drawMode)
	{
		s_Instance->SetDrawMode_Impl(drawMode);
	}

	Renderer::Renderer()
	{
	}
}
