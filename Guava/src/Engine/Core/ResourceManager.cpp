#include "pch.h"
#include "ResourceManager.h"

#include "Engine/Graphics/Texture2D.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/Model.h"
#include "Engine/Graphics/Material.h"

#pragma once
namespace Guava
{
	static scope<ResourceManager> Instance;

	template<typename T>
	T* Contains(ResourceManager::Storage<T>& storage, string_view key)
	{
		auto& result = std::find_if(storage.begin(), storage.end(), [&](auto& pair)
		{
			return pair.first == key;
		});

		if (result == storage.end())
			return nullptr;
		
		return result->second.get();
	}

	/*Textures***********************************************************************/
	Texture2D* ResourceManager::GetTexture(const string_view path)
	{
		scoped_lock lock(Instance->Mutex);

		auto resource = Contains(Instance->Textures, path);

		if(resource) GUAVA_TRACE("Texture2D \"{0}\" was already loaded", path.data());

		return resource;
	}

	void ResourceManager::RegisterTexture(Texture2D* ptr, const string_view path)
	{
		scoped_lock lock(Instance->Mutex);

		if (path.empty())
			Instance->Nameless_Textures.emplace_back(ptr);
		else
			Instance->Textures.try_emplace(path.data(), ptr);
	}

	/*Shaders***********************************************************************/
	Shader* ResourceManager::GetShader(const string_view path)
	{
		scoped_lock lock(Instance->Mutex);

		auto resource = Contains(Instance->Shaders, path);

		if (resource) GUAVA_TRACE("Shader \"{0}\" was already loaded", path.data());

		return resource;
	}

	void ResourceManager::RegisterShader(Shader* ptr, const string_view path)
	{
		scoped_lock lock(Instance->Mutex);

		if (path.empty())
			Instance->Nameless_Shaders.emplace_back(ptr);
		else
			Instance->Shaders.try_emplace(path.data(), ptr);
	}

	/*Models***********************************************************************/
	Model* ResourceManager::GetModel(const string_view path)
	{
		scoped_lock lock(Instance->Mutex);

		auto resource = Contains(Instance->Models, path);

		if (resource) GUAVA_TRACE("Model \"{0}\" was already loaded", path.data());

		return resource;
	}

	void ResourceManager::RegisterModel(Model* ptr, const string_view path)
	{
		scoped_lock lock(Instance->Mutex);

		if (path.empty())
			Instance->Nameless_Models.emplace_back(ptr);
		else
			Instance->Models.try_emplace(path.data(), ptr);
	}

	/*Materials***********************************************************************/
	vector<scope<Material>>& ResourceManager::GetMaterials(const string_view path)
	{
		scoped_lock lock(Instance->Mutex);

		auto& resource = Instance->Materials[path.data()];

		if (!resource.empty()) GUAVA_TRACE("Materials from \"{0}\" were already loaded", path.data());

		return resource;
	}

	void ResourceManager::Create()
	{
		Instance.reset(new ResourceManager());
	}

	/*Cleanup***********************************************************************/
	void ResourceManager::Destroy()
	{
		Instance.reset();
	}
}


