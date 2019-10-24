#include "Guava/Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"
#include "Guava/Core/Log.h"

namespace Guava
{
	Shader* Shader::Create(const ShaderInput& si)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::OpenGL:
			return new OpenGLShader(si);

		default: 
			GUAVA_INVALID_RENDER_API("Shader");
		}

		return nullptr;
	}
}
