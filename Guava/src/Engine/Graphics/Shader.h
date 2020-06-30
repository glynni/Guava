#pragma once
#include "Engine/Core/TextFile.h"

namespace Guava
{
	class Material;

	class Shader
	{
	public:

		virtual ~Shader() = default;
		virtual void Bind() = 0;

		virtual bool SetMat4(const string_view variable, const mat4& matrix) = 0;
		virtual bool SetMat3(const string_view variable, const mat3& matrix) = 0;
		virtual bool SetVec3(const string_view variable, const vec3& vec) = 0;
		virtual bool SetVec4(const string_view variable, const vec4& vec) = 0;
		virtual bool SetFloat(const string_view variable, float i) = 0;
		virtual bool SetBool(const string_view variable, bool b) = 0;
		virtual bool SetInt(const string_view variable, int i) = 0;

		void ApplyMaterial(Material* mat);

		static Shader* LoadFromName(const string_view name);

	protected:

		string		m_VertexCode;
		string		m_FragmentCode;
		Material*	m_CurrentMaterial;

		Shader();

		virtual void GPU_UpdateData() = 0;

		void FreeMemory();
	};
}
