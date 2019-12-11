#pragma once
#include "BufferLayout.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

namespace Guava
{
	typedef std::unordered_map<std::string, std::shared_ptr<Texture>>	TextureAssets;
	typedef std::unordered_map<std::string, std::shared_ptr<Mesh>>		MeshAssets;
	typedef std::unordered_map<Shader*, std::shared_ptr<Shader>>		ShaderAssets;

	struct RendererData
	{
		// Store assets
		TextureAssets	m_Textures;
		MeshAssets		m_Meshes;
		ShaderAssets	m_Shaders;
	};
}
