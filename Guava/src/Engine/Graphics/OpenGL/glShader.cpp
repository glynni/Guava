#include "pch.h"
#include "glShader.h"

namespace Guava::OpenGL
{
	static GLuint s_CurrentProgram = -1;

	static GLuint CreateGLShader(GLenum shaderType, const string_view code)
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
			const GLuint maxLogLength = 500;
			GLchar infoLog[maxLogLength];
			glGetShaderInfoLog(handle, maxLogLength, &length, infoLog);

			// Delete the new line (\n)
			infoLog[length-1] = ' ';

			GUAVA_ERROR("OpenGL Shader compilation error {0}", infoLog);
			GUAVA_ASSERT(false, "Shader compilation failed");
		}

		return handle;
	}

	void glShader::GPU_UpdateData()
	{
		if (!m_Initialized)
		{
			glDeleteProgram(m_ShaderProgram);
			m_ShaderProgram = glCreateProgram();
			s_CurrentProgram = -1;
			m_CurrentMaterial = nullptr;

			GLuint vsShader = CreateGLShader(GL_VERTEX_SHADER, m_VertexCode);
			GLuint fsShader = CreateGLShader(GL_FRAGMENT_SHADER, m_FragmentCode);

			glAttachShader(m_ShaderProgram, vsShader);
			glAttachShader(m_ShaderProgram, fsShader);

			glLinkProgram(m_ShaderProgram);

			// Check successful linking
			GLint status;
			glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &status);
			if (status != GL_TRUE)
			{
				GLsizei length;
				const GLuint maxLogLength = 500;
				GLchar infoLog[maxLogLength];
				glGetProgramInfoLog(m_ShaderProgram, maxLogLength, &length, infoLog);

				// Delete the new line (\n)
				infoLog[length - 1] = ' ';

				GUAVA_ERROR("OpenGL Program compilation error {0}", infoLog);
				GUAVA_ASSERT(false, "Program linking failed");
			}

			glDeleteShader(vsShader);
			glDeleteShader(fsShader);

			FreeMemory();

			m_Initialized = true;
		}
	}

	GLint glShader::GetUniformLocation(const string_view uniform)
	{
		GLint location;

		/* Caching in an unordered_map seemed to be a lot slower..
		const auto result = find_if(m_UniformLocations.begin(), m_UniformLocations.end(),

		[&](const auto& pair)
		{
			return pair.first == uniform;
		});

		if (result == m_UniformLocations.end())
		{
			location = glGetUniformLocation(m_ShaderProgram, uniform.data());
			m_UniformLocations.emplace(uniform, location);

			if (location == -1)
				GUAVA_WARN("Uniform {0} could not be found or isn't used", uniform.data());

			return location;
		}
		else
			location = result->second;
		*/

		location = glGetUniformLocation(m_ShaderProgram, uniform.data());

		if (location == -1)
			GUAVA_WARN("Uniform {0} could not be found or isn't used", uniform.data());

		return location;
	}

	glShader::glShader() : m_Initialized(false)
	{
		m_ShaderProgram = glCreateProgram();
	}

	glShader::~glShader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void glShader::Bind()
	{
		GPU_UpdateData();

		if (s_CurrentProgram != m_ShaderProgram)
		{
			glUseProgram(m_ShaderProgram);
			s_CurrentProgram = m_ShaderProgram;
		}
	}

	bool glShader::SetMat4(const string_view variable, const mat4& matrix)
	{
		auto location = GetUniformLocation(variable);

		if (location == -1) return false;

		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);

		return true;
	}

	bool glShader::SetMat3(const string_view variable, const mat3& matrix)
	{
		auto location = GetUniformLocation(variable);

		if (location == -1) return false;
			
		glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);

		return true;
	}

	bool glShader::SetVec3(const string_view variable, const vec3& vec)
	{
		auto location = GetUniformLocation(variable);

		if (location == -1) return false;
			
		glUniform3fv(location, 1, &vec[0]);

		return true;
	}

	bool glShader::SetVec4(const string_view variable, const vec4& vec)
	{
		auto location = GetUniformLocation(variable);

		if (location == -1) return false;
			
		glUniform4fv(location, 1, &vec[0]);

		return true;
	}

	bool glShader::SetBool(const string_view variable, bool b)
	{
		auto location = GetUniformLocation(variable);

		if (location == -1) return false;
			
		glUniform1i(location, b ? 1 : 0);

		return true;
	}

	bool glShader::SetInt(const string_view variable, int i)
	{
		auto location = GetUniformLocation(variable);

		if (location == -1) return false;
			
		glUniform1i(location, i);

		return true;
	}

	bool glShader::SetFloat(const string_view variable, float i)
	{
		auto location = GetUniformLocation(variable);

		if (location == -1) return false;
			
		glUniform1f(location, i);

		return true;
	}
}