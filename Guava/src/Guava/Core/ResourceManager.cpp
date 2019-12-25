#include "pch.h"
#include "ResourceManager.h"

#include "Guava/Graphics/Texture2D.h"
#include "Guava/Graphics/Shader.h"
#include "Guava/Graphics/Model.h"
#include "Guava/Graphics/Material.h"

#pragma once
namespace Guava
{
	template<typename T>
	using Storage = u_map<string, scope<T>>;

	template<typename T>
	using Storage_Nameless = vector<scope<T>>;

	static mutex Mutex;

	static Storage<Texture2D>	Textures;
	static Storage<Shader>	Shaders;
	static Storage<Model>	Models;

	static Storage_Nameless<Texture2D>	Nameless_Textures;
	static Storage_Nameless<Shader>		Nameless_Shaders;
	static Storage_Nameless<Model>		Nameless_Models;

	static u_map<string, vector<scope<Material>>> Materials;

	template<typename T>
	T* Contains(Storage<T>& storage, string_view key)
	{
		auto& result = std::find_if(storage.begin(), storage.end(), [&](auto& pair)
		{
			return pair.first == key;
		});

		if (result == storage.end())
			return nullptr;

		GUAVA_TRACE("{0} was already loaded", key.data());
		return result->second.get();
	}

	/*Textures***********************************************************************/
	Texture2D* ResourceManager::GetTexture(const string_view path)
	{
		scoped_lock lock(Mutex);

		return Contains(Textures, path);
	}

	void ResourceManager::RegisterTexture(Texture2D* ptr, const string_view path)
	{
		scoped_lock lock(Mutex);

		if (path.empty())
			Nameless_Textures.emplace_back(ptr);
		else
			Textures.try_emplace(path.data(), ptr);
	}

	/*Shaders***********************************************************************/
	Shader* ResourceManager::GetShader(const string_view path)
	{
		scoped_lock lock(Mutex);

		return Contains(Shaders, path);
	}

	void ResourceManager::RegisterShader(Shader* ptr, const string_view path)
	{
		scoped_lock lock(Mutex);

		if (path.empty())
			Nameless_Shaders.emplace_back(ptr);
		else
			Shaders.try_emplace(path.data(), ptr);
	}

	/*Models***********************************************************************/
	Model* ResourceManager::GetModel(const string_view path)
	{
		scoped_lock lock(Mutex);

		return Contains(Models, path);
	}

	void ResourceManager::RegisterModel(Model* ptr, const string_view path)
	{
		scoped_lock lock(Mutex);

		if (path.empty())
			Nameless_Models.emplace_back(ptr);
		else
			Models.try_emplace(path.data(), ptr);
	}

	/*Materials***********************************************************************/
	vector<scope<Material>>& ResourceManager::GetMaterials(const string_view path)
	{
		scoped_lock lock(Mutex);

		return Materials[path.data()];
	}

	/*Cleanup***********************************************************************/
	void ResourceManager::Destroy()
	{
		scoped_lock lock(Mutex);

		Textures = Storage<Texture2D>();
		Shaders = Storage<Shader>();
		Models = Storage<Model>();
		Materials = u_map<string, vector<scope<Material>>>();

		Nameless_Textures = Storage_Nameless<Texture2D>();
		Nameless_Shaders = Storage_Nameless<Shader>();
		Nameless_Models = Storage_Nameless<Model>();
	}
}


