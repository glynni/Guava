#pragma once
#include "../Shader.h"

namespace Guava::OpenGL
{
	class glShader : public Shader
	{
	public:

		glShader();
		~glShader();

		void Bind() override;

		void SetMat4(const string_view variable, const mat4& matrix) override;
		void SetMat3(const string_view variable, const mat3& matrix) override;
		void SetVec3(const string_view variable, const vec3& vec) override;
		void SetVec4(const string_view variable, const vec4& vec) override;
		void SetBool(const string_view variable, bool b) override;
		void SetInt(const string_view variable, int i) override;
		void SetFloat(const string_view variable, float i) override;

	private:

		GLuint	m_ShaderProgram;
		bool	m_Initialized;

		void UpdateGPU() override;

		//u_map<string, GLint> m_UniformLocations;
		GLint GetUniformLocation(const string_view uniform);
	};
}


