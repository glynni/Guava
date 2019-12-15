#pragma once
#include "Guava/Graphics/Shader.h"

namespace Guava::OpenGL
{
	class glShader : public Guava::Shader
	{
	public:

		glShader(const StringView name);
		~glShader();

		void Bind() override;

		void SetMat4(const StringView variable, const glm::mat4& matrix) override;
		void SetMat3(const StringView variable, const glm::mat3& matrix) override;
		void SetVec4(const StringView variable, const glm::vec4& vec) override;
		void SetBool(const StringView variable, bool b) override;
		void SetInt(const StringView variable, int i) override;
		void SetFloat(const StringView variable, float i) override;

	private:

		GLuint m_ShaderProgram;
		GLuint m_VertexShader;
		GLuint m_FragmentShader;

		std::unordered_map<std::string, GLint> m_UniformLocations;

		void LoadFromFiles();
		GLint GetUniformLocation(const StringView uniform);
	};
}


