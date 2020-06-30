#pragma once

namespace Guava::OpenGL
{
	class glVertexArray
	{
	public:

		glVertexArray();
		~glVertexArray();

		void Bind() const;

	private:

		GLuint m_OpenGLHandle;
	};
}
