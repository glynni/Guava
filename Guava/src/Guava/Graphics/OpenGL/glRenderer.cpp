#include "pch.h"
#include "glRenderer.h"
#include "Guava/Core/Log.h"
#include "Guava/Graphics/RendererData.h"

namespace Guava::OpenGL
{
	glRenderer::glRenderer()
	{
		Prepare();

		GUAVA_CORE_INFO("Created OpenGL renderer.");
		glEnable(GL_DEPTH_TEST);
	}

	glRenderer::~glRenderer()
	{
		GUAVA_CORE_INFO("Destroyed OpenGL renderer.");
	}

	void glRenderer::ClearScreen_Impl()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void glRenderer::SetViewport_Impl(const glm::uvec2& size, const glm::uvec2& bottomLeft)
	{
		glViewport(bottomLeft.x, bottomLeft.y, size.x, size.y);
	}

	void glRenderer::SetClearColor_Impl(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void glRenderer::Prepare()
	{
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GUAVA_ASSERT(status, "GLAD could not be loaded.");

		// Debug callbacks
#if defined GUAVA_DEBUG

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* userParam)
			{
				switch (severity)
				{
				case GL_DEBUG_SEVERITY_HIGH:
					GUAVA_CORE_ERROR("OpenGL error: {0}", msg); break;

				case GL_DEBUG_SEVERITY_MEDIUM:
					GUAVA_CORE_WARN("OpenGL warning: {0}", msg); break;

				case GL_DEBUG_SEVERITY_LOW:
					GUAVA_CORE_WARN("OpenGL warning: {0}", msg); break;

				case GL_DEBUG_SEVERITY_NOTIFICATION:
					break;// GUAVA_CORE_TRACE("OpenGL: {0}", msg); break;

				default: break;
				}

			}, nullptr);

#endif
	}
}
