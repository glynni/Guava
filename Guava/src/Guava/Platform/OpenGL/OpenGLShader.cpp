#include "OpenGLShader.h"

namespace Guava
{
	static GLuint CreateGLShader(GLenum shaderType, const std::string& code)
	{
		GLuint handle = glCreateShader(shaderType);

		auto c_code = code.c_str();
		glShaderSource(handle, 1, &c_code, nullptr);
		glCompileShader(handle);

		return handle;
	}

	OpenGLShader::OpenGLShader(const ShaderInput& si) :
		m_ShaderProgram(0), m_VertexShader(0), m_FragmentShader(0)
	{
		m_ShaderProgram = glCreateProgram();

		m_VertexShader = CreateGLShader(GL_VERTEX_SHADER, si.VertexShaderCode);
		m_FragmentShader = CreateGLShader(GL_FRAGMENT_SHADER, si.FragmentShaderCode);

		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);

		glLinkProgram(m_ShaderProgram);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgram);

		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
	}

	void OpenGLShader::Use()
	{
		glUseProgram(m_ShaderProgram);
	}
}