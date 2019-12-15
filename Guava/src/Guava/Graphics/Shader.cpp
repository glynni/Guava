#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Guava/Core/Utility.h"
#include "Guava/Core/AssetManager.h"

namespace Guava
{
	static const String s_VsEnding("_vertex.glsl");
	static const String s_FsEnding("_fragment.glsl");

	Shader* Shader::Create(const StringView name)
	{
		return AssetManager::GetShader(name);
	}

	Shader::Shader(const StringView filePath)
	{
		m_VertexFile.reset(new File::TextFile(filePath.data() + s_VsEnding));
		m_FragmentFile.reset(new File::TextFile(filePath.data() + s_FsEnding));
	}
}

