#include "pch.h"
#include "Guava/Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Guava
{
	Shader* Shader::Create(const ShaderFiles& sf)
	{
		Shader* shader = nullptr;

		switch (Renderer::GetAPI())
		{
			case RenderAPI::OpenGL:
			{
				shader = new OpenGLShader(sf);
			}
			break;

			default: 
				GUAVA_INVALID_RENDER_API("Shader");
		}

		if (shader)
			Renderer::AddShader(shader);

		return shader;
	}
}
