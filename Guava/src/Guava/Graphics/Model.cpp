#include "pch.h"
#include "Model.h"
#include "Guava/Core/AssetManager.h"

namespace Guava
{
	Model::Model(const std::string_view filePath)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filePath.data(),
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		GUAVA_ASSERT(scene != nullptr, std::string("Model \"") + filePath.data() + "\" could not be loaded");
	}

	Model* Model::Create(const std::string_view filePath)
	{
		return AssetManager::GetModel(filePath);
	}
}
