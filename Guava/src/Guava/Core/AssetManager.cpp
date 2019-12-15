#include "pch.h"
#include "AssetManager.h"

namespace Guava
{
	// Asset paths
	static const std::string AssetDir =		"assets/";
	static const std::string TextureDir =	"";
	static const std::string ShaderDir =	AssetDir + "shaders/";
	static const std::string ModelDir =		AssetDir + "models/";

	// Asset storage
	template<typename T>
	using Storage = std::unordered_map<std::string, std::unique_ptr<T>>;

	static Storage<Texture>	Textures;
	static Storage<Shader>	Shaders;
	static Storage<Model>	Models;

	template<typename T>
	static T* Contains(const Storage<T>& container, StringView key)
	{
		auto& result = std::find_if(container.begin(), container.end(), [&](auto& pair)
		{
			return pair.first == key;
		});

		if (result != container.end())
			return result->second.get();
		
		return nullptr;
	}

	Texture* AssetManager::GetTexture(const StringView file, const TextureCreationInfo& info)
	{
		std::string key = TextureDir + file.data();

		Texture* t = Contains(Textures, key);

		if (t) 
		{ 
			GUAVA_CORE_TRACE("Texture already exists: {0}", file.data());
			return t;
		}

		t = Renderer::CreateTexture(key, info);

		Textures.emplace(key, t);

		GUAVA_CORE_INFO("Loaded texture: {0}", key);

		return t;
	}

	Shader* AssetManager::GetShader(const StringView name)
	{
		std::string key = ShaderDir + name.data();

		Shader* s = Contains(Shaders, key);

		if (s)
		{
			GUAVA_CORE_TRACE("Shader already exists: {0}", name.data());
			return s;
		}

		s = Renderer::CreateShader(key);

		Shaders.emplace(key, s);

		GUAVA_CORE_INFO("Loaded shader: {0}", key);

		return s;
	}

	Model* AssetManager::GetModel(const StringView file)
	{
		std::string key = ModelDir + file.data();

		Model* m = Contains(Models, key);

		if (m)
		{
			GUAVA_CORE_TRACE("Model already exists: {0}", file.data());
			return m;
		}

		m = Renderer::CreateModel(key);

		Models.emplace(key, m);

		GUAVA_CORE_INFO("Loaded model: {0}", key);

		return m;
	}

	void AssetManager::Destroy()
	{
		Textures.clear();
		Shaders.clear();
		Models.clear();
	}
}
