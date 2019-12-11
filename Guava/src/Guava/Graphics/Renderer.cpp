#include "pch.h"
#include "OpenGL/glRenderer.h"
#include "OpenGL/glTexture.h"
#include "OpenGL/glMesh.h"
#include "RendererData.h"

namespace Guava
{
	RenderAPI s_RenderAPI;
	std::unique_ptr<Renderer> s_Instance;

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
				s_Instance.reset(new OpenGL::glRenderer()); 
				break;

			default:
				GUAVA_INVALID_RENDER_API("Renderer");
				break;
		}
	}

	void Renderer::Destroy()
	{
		s_Instance.reset();
	}

	void Renderer::ClearScreen()
	{
		s_Instance->ClearScreen_Impl();
	}

	void Renderer::SetClearColor(const Color& color)
	{
		s_Instance->SetClearColor_Impl(color);
	}

	void Renderer::Draw(Mesh* mesh, Shader* shader, const Transform& transform, const Camera& camera)
	{
		shader->Bind();

		shader->SetMat4("u_ModelMatrix", transform.GetTransform());
		shader->SetMat4("u_ViewMatrix", camera.GetViewMatrix());
		shader->SetMat4("u_ProjectionMatrix", glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f));
		shader->SetVec4("u_EyePos", { camera.GetPosition() , 1.0f});

		mesh->Draw();
	}
	
	Texture* Renderer::CreateTexture(const Texture::Description& description, const std::string_view filePath)
	{
		Texture* t;

		switch (s_RenderAPI)
		{
		case RenderAPI::OpenGL:
			t = new OpenGL::glTexture(description, filePath);
			break;

		default:
			GUAVA_INVALID_RENDER_API("Renderer");
			break;
		}

		s_Instance->m_Data->m_Textures.emplace(filePath.data(), t);
		return t;
	}

	Mesh* Renderer::CreateMesh(const std::string_view filePath)
	{
		Mesh* m;

		switch (s_RenderAPI)
		{
		case RenderAPI::OpenGL:
			m = new OpenGL::glMesh(filePath);
			break;

		default:
			GUAVA_INVALID_RENDER_API("Renderer");
			break;
		}

		s_Instance->m_Data->m_Meshes.emplace(filePath.data(), m);
		return m;
	}

	Shader* Renderer::CreateShader(const Shader::Files& files)
	{
		Shader::Code code;
		code.Load(files);
		return CreateShader(code);
	}

	Shader* Renderer::CreateShader(const Shader::Code& code)
	{
		Shader* s;

		switch (s_RenderAPI)
		{
		case RenderAPI::OpenGL:
			s = new OpenGL::glShader(code);
			break;

		default:
			GUAVA_INVALID_RENDER_API("Renderer");
			break;
		}

		s_Instance->m_Data->m_Shaders.emplace(s, s);
		return s;
	}

	void Renderer::SetViewport(const glm::uvec2& size, const glm::uvec2& bottomLeft)
	{
		s_Instance->SetViewport_Impl(size, bottomLeft);
	}

	Renderer::Renderer()
	{
		m_Data.reset(new RendererData());
	}
}
