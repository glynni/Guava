#pragma once
#include "Guava/Renderer/Shader.h"

namespace Guava 
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const ShaderFiles& si);
		~OpenGLShader();

		void Use() override;

	private:

		GLuint m_ShaderProgram;
		GLuint m_VertexShader, m_FragmentShader;
	};
}


