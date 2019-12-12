#include "pch.h"
#include "AssetManager.h"

namespace Guava
{
	// Asset paths
	static const std::string AssetDir =		"assets/";
	static const std::string TextureDir =	AssetDir + "textures/";
	static const std::string ShaderDir =	AssetDir + "shaders/";
	static const std::string ModelDir =		AssetDir + "models/";

	// Asset storage
	template<typename T>
	using Storage = std::unordered_map<std::string, std::unique_ptr<T>>;

	static Storage<Texture>	Textures;
	static Storage<Shader>	Shaders;
	static Storage<Model>	Models;

	template<typename T>
	static T* Contains(const Storage<T>& container, std::string_view key)
	{
		auto& result = std::find_if(container.begin(), container.end(), [&](auto& pair)
		{
			return pair.first == key;
		});

		if (result != container.end())
			return result->second.get();
		
		return nullptr;
	}

	Texture* AssetManager::GetTexture(const std::string_view file, const Texture::Description& description)
	{
		std::string key = TextureDir + file.data();

		Texture* t = Contains(Textures, key);

		if (t) 
		{ 
			GUAVA_CORE_TRACE("Texture \"{0}\" already exists.", file.data());
			return t;
		}

		t = Renderer::CreateTexture(key, description);

		Textures.emplace(key, t);

		return t;
	}

	Shader* AssetManager::GetShader(const std::string_view name)
	{
		std::string key = ShaderDir + name.data();

		Shader* s = Contains(Shaders, key);

		if (s)
		{
			GUAVA_CORE_TRACE("Shader \"{0}\" already exists.", name.data());
			return s;
		}

		s = Renderer::CreateShader(key);

		Shaders.emplace(key, s);

		return s;
	}

	Model* AssetManager::GetModel(const std::string_view file)
	{
		std::string key = ModelDir + file.data();

		Model* m = Contains(Models, key);

		if (m)
		{
			GUAVA_CORE_TRACE("Model \"{0}\" already exists.", file.data());
			return m;
		}

		m = new Model(key);

		Models.emplace(key, m);

		return m;
	}

	void AssetManager::ClearAssets()
	{
		Textures.clear();
		Shaders.clear();
		Models.clear();
	}
}
