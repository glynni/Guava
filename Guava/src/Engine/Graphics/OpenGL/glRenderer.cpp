#include "pch.h"
#include "glRenderer.h"
#include "Engine/Core/Log.h"

namespace Guava::OpenGL
{
	glRenderer::glRenderer()
	{
		Prepare();

		glEnable(GL_DEPTH_TEST);

		GUAVA_INFO("Created OpenGL renderer");
	}

	glRenderer::~glRenderer()
	{
		GUAVA_INFO("Destroyed OpenGL renderer");
	}

	void glRenderer::ClearScreen_Impl()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void glRenderer::ClearDepth_Impl()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void glRenderer::SetViewport_Impl(const uvec2& size, const uvec2& bottomLeft)
	{
		glViewport(bottomLeft.x, bottomLeft.y, size.x, size.y);
	}

	void glRenderer::SetClearColor_Impl(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void glRenderer::SetDrawMode_Impl(const FillMode drawMode)
	{
		switch (drawMode)
		{
		case FillMode::Polygon:		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case FillMode::Wireframe:	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		default:
			break;
		}
	}

	Model* glRenderer::CreateModel_Impl()
	{
		return new glModel();
	}

	Texture2D* glRenderer::CreateTexture2D_Impl(const Texture2DCreateInfo& tci)
	{
		return new glTexture2D(tci);
	}

	Shader* glRenderer::CreateShader_Impl()
	{
		return new glShader();
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
					GUAVA_ERROR("OpenGL: {0}", msg); break;

				case GL_DEBUG_SEVERITY_MEDIUM:
					GUAVA_WARN("OpenGL: {0}", msg); break;

				case GL_DEBUG_SEVERITY_LOW:
					GUAVA_WARN("OpenGL: {0}", msg); break;

				case GL_DEBUG_SEVERITY_NOTIFICATION:
					break;// GUAVA_TRACE("OpenGL: {0}", msg); break;

				default: break;
				}

			}, nullptr);

#endif
	}
}
