#pragma once
#include "Guava/Graphics/Shader.h"

namespace Guava::OpenGL
{
	class glShader : public Guava::Shader
	{
	public:

		glShader(const std::string_view name);
		~glShader();

		void Bind() override;

		void SetMat4(const std::string_view variable, const glm::mat4& matrix) override;
		void SetMat3(const std::string_view variable, const glm::mat3& matrix) override;
		void SetVec4(const std::string_view variable, const glm::vec4& vec) override;
		void SetBool(const std::string_view variable, bool b) override;
		void SetInt(const std::string_view variable, int i) override;
		void SetFloat(const std::string_view variable, float i) override;

	private:

		GLuint m_ShaderProgram;
		GLuint m_VertexShader;
		GLuint m_FragmentShader;

		std::unordered_map<std::string, GLint> m_UniformLocations;

		void LoadFromCode(const glShader::Code& code);
		GLint GetUniformLocation(const std::string_view uniform);
	};
}


