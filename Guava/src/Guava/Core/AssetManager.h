#pragma once
#include "Guava/Graphics/Renderer.h"

namespace Guava
{
	class AssetManager
	{
	public:

		static Texture*	GetTexture(const StringView file, const TextureCreationInfo& info);
		static Shader*	GetShader(const StringView name);
		static Model*	GetModel(const StringView file);

		static void Destroy();
	};
}

