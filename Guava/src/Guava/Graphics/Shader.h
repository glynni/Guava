#pragma once

namespace Guava
{
	class Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void Bind() = 0;

		virtual void SetMat4(const StringView variable, const glm::mat4& matrix) = 0;
		virtual void SetMat3(const StringView variable, const glm::mat3& matrix) = 0;
		virtual void SetVec4(const StringView variable, const glm::vec4& vec) = 0;
		virtual void SetBool(const StringView variable, bool b) = 0;
		virtual void SetInt(const StringView variable, int i) = 0;
		virtual void SetFloat(const StringView variable, float i) = 0;

		static Shader* Create(const StringView name);

	protected:

		Shader(const StringView name);

		std::unique_ptr<File::TextFile> m_VertexFile;
		std::unique_ptr<File::TextFile> m_FragmentFile;
	};
}
