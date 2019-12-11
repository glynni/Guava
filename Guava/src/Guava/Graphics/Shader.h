#pragma once

namespace Guava
{
	class Shader
	{
	public:

		struct Code
		{
			std::string VertexShader;
			std::string FragmentShader;
		};

		virtual ~Shader() = default;

		virtual void Bind() = 0;

		virtual void SetMat4(const std::string_view variable, const glm::mat4& matrix) = 0;
		virtual void SetVec4(const std::string_view variable, const glm::vec4& vec) = 0;
		virtual void SetBool(const std::string_view variable, bool b) = 0;
		virtual void SetInt(const std::string_view variable, int i) = 0;

		static Shader* Create(const std::string_view name);

	protected:

		Shader(const std::string_view name);

		Shader::Code m_Code;
	};
}
