#include "pch.h"
#include "OpenGLRenderer.h"

Guava::OpenGLRenderer::OpenGLRenderer()
{
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	GUAVA_ASSERT(status, "GLAD could not be loaded.");

	GUAVA_CORE_INFO("Created OpenGL renderer.");

	// Debug callbacks
	#ifdef GUAVA_DEBUG
		
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* userParam)
		{
				switch (severity)
				{
				case GL_DEBUG_SEVERITY_HIGH:
					GUAVA_CORE_ERROR("OpenGL error: {0}", msg); break;

				case GL_DEBUG_SEVERITY_MEDIUM:
					GUAVA_CORE_ERROR("OpenGL warning: {0}", msg); break;

				case GL_DEBUG_SEVERITY_LOW:
					GUAVA_CORE_WARN("OpenGL warning: {0}", msg); break;

				case GL_DEBUG_SEVERITY_NOTIFICATION:
					break;// GUAVA_CORE_TRACE("OpenGL: {0}", msg); break;

				default: break;
				}

		}, nullptr);

	#endif

	glClearColor(.2f, .2f, .5f, 1.f);
}

Guava::OpenGLRenderer::~OpenGLRenderer()
{
	GUAVA_CORE_INFO("Destroyed OpenGL renderer.");
}

void Guava::OpenGLRenderer::ClearScreen_Impl()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
