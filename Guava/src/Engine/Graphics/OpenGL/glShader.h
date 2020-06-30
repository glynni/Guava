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

		bool SetMat4(const string_view variable, const mat4& matrix) override;
		bool SetMat3(const string_view variable, const mat3& matrix) override;
		bool SetVec3(const string_view variable, const vec3& vec) override;
		bool SetVec4(const string_view variable, const vec4& vec) override;
		bool SetBool(const string_view variable, bool b) override;
		bool SetInt(const string_view variable, int i) override;
		bool SetFloat(const string_view variable, float i) override;

	private:

		GLuint	m_ShaderProgram;
		bool	m_Initialized;

		void GPU_UpdateData() override;

		//u_map<string, GLint> m_UniformLocations;
		GLint GetUniformLocation(const string_view uniform);
	};
}


