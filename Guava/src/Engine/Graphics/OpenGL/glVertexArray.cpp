#include "pch.h"
#include "glVertexArray.h"

namespace Guava::OpenGL
{
	static GLuint s_CurrentArray = -1;

	glVertexArray::glVertexArray()
	{
		glGenVertexArrays(1, &m_OpenGLHandle);
	}

	glVertexArray::~glVertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGLHandle);
	}

	void glVertexArray::Bind() const
	{
		if (s_CurrentArray != m_OpenGLHandle)
		{
			glBindVertexArray(m_OpenGLHandle);
			s_CurrentArray = m_OpenGLHandle;
		}
	}
}