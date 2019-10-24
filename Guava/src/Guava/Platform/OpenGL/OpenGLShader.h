#pragma once
#include "Guava/Renderer/Shader.h"

#include <glad/glad.h>

namespace Guava 
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const ShaderInput& si);
		~OpenGLShader();

		void Use() override;

	private:

		GLuint m_ShaderProgram;
		GLuint m_VertexShader, m_FragmentShader;
	};
}


