#include "pch.h"
#include "glShader.h"

namespace Guava::OpenGL
{
	GLuint s_CurrentProgram = -1;

	GLuint CreateGLShader(GLenum shaderType, const std::string_view code)
	{
		GLuint handle = glCreateShader(shaderType);
		GLint status;

		auto c_code = code.data();
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

			GUAVA_CORE_ERROR("OGL error: Shader compilation error {0}", infoLog);
			GUAVA_ASSERT(false, "Shader compilation failed");
		}

		return handle;
	}

	GLint glShader::GetUniformLocation(const std::string_view uniform)
	{
		GLint location;
		const auto& result = std::find_if(m_UniformLocations.begin(), m_UniformLocations.end(),

			[&](auto& pair)
			{
				return pair.first == uniform;
			});

		if (result == m_UniformLocations.end())
		{
			location = glGetUniformLocation(m_ShaderProgram, uniform.data());
			m_UniformLocations.emplace(uniform, location);

			if (location == -1)
				GUAVA_CORE_WARN("Uniform {0} could not be found", uniform.data());

			return location;
		}
		else
			return result->second;
	}

	glShader::glShader(const std::string_view name) : Guava::Shader(name),
		m_ShaderProgram(0), m_VertexShader(0), m_FragmentShader(0)
	{
		LoadFromCode(m_Code);
	}

	glShader::~glShader()
	{
		glDeleteProgram(m_ShaderProgram);

		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
	}

	void glShader::Bind()
	{
		if (s_CurrentProgram != m_ShaderProgram)
		{
			glUseProgram(m_ShaderProgram);
			s_CurrentProgram = m_ShaderProgram;
		}
	}

	void glShader::SetMat4(const std::string_view variable, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(variable), 1, GL_FALSE, &matrix[0][0]);
	}

	void glShader::SetVec4(const std::string_view variable, const glm::vec4& vec)
	{
		glUniform4fv(GetUniformLocation(variable), 1, &vec[0]);
	}

	void glShader::SetBool(const std::string_view variable, bool b)
	{
		glUniform1i(GetUniformLocation(variable), b ? 1 : 0);
	}

	void glShader::SetInt(const std::string_view variable, int i)
	{
		glUniform1i(GetUniformLocation(variable), i);
	}

	void glShader::LoadFromCode(const glShader::Code& code)
	{
		m_ShaderProgram = glCreateProgram();

		m_VertexShader = CreateGLShader(GL_VERTEX_SHADER, code.VertexShader);
		m_FragmentShader = CreateGLShader(GL_FRAGMENT_SHADER, code.FragmentShader);

		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);

		glLinkProgram(m_ShaderProgram);

		// Free Memory
		m_Code = Shader::Code();
	}
}