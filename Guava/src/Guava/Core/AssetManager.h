#pragma once
#include "Guava/Graphics/Renderer.h"

namespace Guava
{
	class AssetManager
	{
	public:

		static Texture*	GetTexture(const std::string_view file, const TextureCreationInfo& info);
		static Shader*	GetShader(const std::string_view name);
		static Model*	GetModel(const std::string_view file);

		static void Destroy();
	};
}

