#pragma once
#include <string>

namespace Guava
{
	struct ShaderFiles
	{
		std::string VertexShaderFile;
		std::string FragmentShaderFile;
	};

	class Shader
	{
	public:

		static Shader* Create(const ShaderFiles& sf);

		virtual ~Shader() {};

		virtual void Use() = 0;
	};
}
