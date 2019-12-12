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

		size_t numVertices = 0;
		size_t numIndices = 0;

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			
			if (mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			{
				GUAVA_CORE_WARN("{0} in {1} was not loaded: Unsupported primitive types", mesh->mName.C_Str(), filePath.data());
				continue;
			}

			numVertices += mesh->mNumVertices;
			numIndices += size_t(mesh->mNumFaces * 3);

			m_Meshes.emplace_back(Renderer::CreateMesh(mesh));
		}

		GUAVA_CORE_TRACE("Model loaded: {0}", filePath.data());
		GUAVA_CORE_TRACE(" meshes: {0}", m_Meshes.size());
		GUAVA_CORE_TRACE(" vertices: {0}", numVertices);
		GUAVA_CORE_TRACE(" indices: {0}", numIndices);
	}

	const MeshList& Model::GetMeshList() const
	{
		return m_Meshes;
	}

	Model* Model::Create(const std::string_view filePath)
	{
		return AssetManager::GetModel(filePath);
	}
}
