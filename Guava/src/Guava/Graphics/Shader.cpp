#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Guava/Core/Utility.h"

namespace Guava
{
	const char* ShaderFolder = "src/Guava/Graphics/Shaders/";

	bool Shader::Code::Load(const Shader::Files& files)
	{
		VertexShader = ReadTextFile(ShaderFolder + files.VertexShader);
		FragmentShader = ReadTextFile(ShaderFolder + files.FragmentShader);

		return true;
	}

	Shader* Shader::Create(const Shader::Files& files)
	{
		return Renderer::CreateShader(files);
	}

	Shader* Shader::Create(const Shader::Code& Code)
	{
		return Renderer::CreateShader(Code);
	}
}

