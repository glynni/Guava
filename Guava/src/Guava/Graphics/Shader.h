#pragma once

namespace Guava
{
	class Shader
	{
	public:

		struct Files
		{
			std::string VertexShader;
			std::string FragmentShader;
		};

		struct Code
		{
			std::string VertexShader;
			std::string FragmentShader;

			bool Load(const Shader::Files& files);
		};

		virtual ~Shader() = default;

		virtual void Bind() = 0;

		virtual void SetMat4(const std::string_view variable, const glm::mat4& matrix) = 0;
		virtual void SetVec4(const std::string_view variable, const glm::vec4& vec) = 0;
		virtual void SetBool(const std::string_view variable, bool b) = 0;
		virtual void SetInt(const std::string_view variable, int i) = 0;

		static Shader* Create(const Shader::Files& files);
		static Shader* Create(const Shader::Code& Code);
	};
}
