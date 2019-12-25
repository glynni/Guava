#pragma once
#include "Guava/Core/TextFile.h"

namespace Guava
{
	class Material;

	class Shader
	{
	public:

		virtual ~Shader() = default;
		virtual void Bind() = 0;

		virtual void SetMat4(const string_view variable, const mat4& matrix) = 0;
		virtual void SetMat3(const string_view variable, const mat3& matrix) = 0;
		virtual void SetVec3(const string_view variable, const vec3& vec) = 0;
		virtual void SetVec4(const string_view variable, const vec4& vec) = 0;
		virtual void SetBool(const string_view variable, bool b) = 0;
		virtual void SetInt(const string_view variable, int i) = 0;
		virtual void SetFloat(const string_view variable, float i) = 0;

		void ApplyMaterial(Material* mat);

		static Shader* LoadFromFiles(const string_view vsFile, const string_view fsFile);

	protected:

		string		m_VertexCode;
		string		m_FragmentCode;
		Material*	m_CurrentMaterial;

		Shader();

		virtual void UpdateGPU() = 0;

		void FreeData();
	};
}
