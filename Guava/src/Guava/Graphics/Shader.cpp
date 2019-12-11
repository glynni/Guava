#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Guava/Core/Utility.h"
#include "Guava/Core/AssetManager.h"

namespace Guava
{
	Shader* Shader::Create(const std::string_view name)
	{
		return AssetManager::GetShader(name);
	}

	Shader::Shader(const std::string_view filePath)
	{
		m_Code.VertexShader = ReadTextFile(std::string(filePath) + "_vertex.glsl");
		m_Code.FragmentShader = ReadTextFile(std::string(filePath) + "_fragment.glsl");
	}
}

