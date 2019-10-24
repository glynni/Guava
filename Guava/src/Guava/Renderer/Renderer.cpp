#include "Guava/Platform/OpenGL/OpenGLRenderer.h"
#include "Guava/Core/Log.h"

namespace Guava
{
	RenderAPI Renderer::s_RenderAPI = RenderAPI::OpenGL;
	std::unique_ptr<Renderer> Renderer::m_Renderer;

	void Renderer::Create(RenderAPI api)
	{
		s_RenderAPI = api;
		Destroy();

		switch (api)
		{

		case RenderAPI::OpenGL:
		{
			m_Renderer = std::make_unique<OpenGLRenderer>();
		}
		break;

		default:
			GUAVA_INVALID_RENDER_API("Renderer");
		}
	}

	void Renderer::Destroy()
	{
		m_Renderer.reset();
	}

	void Renderer::ClearScreen()
	{
		m_Renderer->Clear();
	}

	const RenderAPI Renderer::GetAPI()
	{
		return s_RenderAPI;
	}
}
