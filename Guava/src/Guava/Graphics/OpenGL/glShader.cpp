#include "pch.h"
#include "glShader.h"

namespace Guava::OpenGL
{
	static GLuint s_CurrentProgram = -1;

	static GLuint CreateGLShader(GLenum shaderType, const StringView code)
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

			GUAVA_CORE_ERROR("OpenGL Shader compilation error {0}", infoLog);
			GUAVA_ASSERT(false, "Shader compilation failed");
		}

		return handle;
	}

	GLint glShader::GetUniformLocation(const StringView uniform)
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
				GUAVA_CORE_WARN("Uniform {0} could not be found or isn't used", uniform.data());

			return location;
		}
		else
			return result->second;
	}

	glShader::glShader(const StringView name) : Guava::Shader(name),
		m_ShaderProgram(0), m_VertexShader(0), m_FragmentShader(0)
	{
		LoadFromFiles();
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

	void glShader::SetMat4(const StringView variable, const glm::mat4& matrix)
	{
		auto location = GetUniformLocation(variable);

		if(location != -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void glShader::SetMat3(const StringView variable, const glm::mat3& matrix)
	{
		auto location = GetUniformLocation(variable);

		if (location != -1)
			glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void glShader::SetVec4(const StringView variable, const glm::vec4& vec)
	{
		auto location = GetUniformLocation(variable);

		if (location != -1)
			glUniform4fv(location, 1, &vec[0]);
	}

	void glShader::SetBool(const StringView variable, bool b)
	{
		auto location = GetUniformLocation(variable);

		if (location != -1)
			glUniform1i(location, b ? 1 : 0);
	}

	void glShader::SetInt(const StringView variable, int i)
	{
		auto location = GetUniformLocation(variable);

		if (location != -1)
			glUniform1i(location, i);
	}

	void glShader::SetFloat(const StringView variable, float i)
	{
		auto location = GetUniformLocation(variable);

		if (location != -1)
			glUniform1f(location, i);
	}

	void glShader::LoadFromFiles()
	{
		m_ShaderProgram = glCreateProgram();

		m_VertexShader = CreateGLShader(GL_VERTEX_SHADER, m_VertexFile->GetContent());
		m_FragmentShader = CreateGLShader(GL_FRAGMENT_SHADER, m_FragmentFile->GetContent());

		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);

		glLinkProgram(m_ShaderProgram);

		// Free Memory
		m_VertexFile.reset();
		m_FragmentFile.reset();
	}
}