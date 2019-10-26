#include "pch.h"
#include "OpenGLShader.h"
#include "Guava/Core/File.h"

namespace Guava
{
	static GLuint s_CurrentProgram = -1;

	static GLuint CreateGLShader(GLenum shaderType, const std::string& file)
	{
		GLuint handle = glCreateShader(shaderType);
		std::string code = File::ReadTextFile(file);
		GLint status;

		auto c_code = code.c_str();
		glShaderSource(handle, 1, &c_code, nullptr);
		glCompileShader(handle);

		// Check successful compilation
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLsizei length;
			const GLuint maxLogLength = 200;
			GLchar infoLog[maxLogLength];
			glGetShaderInfoLog(handle, maxLogLength, &length, infoLog);

			// Delete the new line (\n)
			infoLog[length-1] = ' ';

			GUAVA_CORE_ERROR("OpenGL error: Shader compilation error in file {0}, {1}", file, infoLog);
		}

		return handle;
	}

	OpenGLShader::OpenGLShader(const ShaderFiles& si) :
		m_ShaderProgram(0), m_VertexShader(0), m_FragmentShader(0)
	{
		m_ShaderProgram = glCreateProgram();

		m_VertexShader = CreateGLShader(GL_VERTEX_SHADER, si.VertexShaderFile);
		m_FragmentShader = CreateGLShader(GL_FRAGMENT_SHADER, si.FragmentShaderFile);

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
		if (s_CurrentProgram != m_ShaderProgram)
		{
			glUseProgram(m_ShaderProgram);
			s_CurrentProgram = m_ShaderProgram;
		}
	}
}