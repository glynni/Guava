#pragma once
#include <string>

namespace Guava
{
	struct ShaderInput
	{
		std::string VertexShaderCode;
		std::string FragmentShaderCode;
	};

	class Shader
	{
	public:

		static Shader* Create(const ShaderInput& si);

		virtual ~Shader() {};

		virtual void Use() = 0;
	};
}
