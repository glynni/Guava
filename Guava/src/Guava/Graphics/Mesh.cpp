#include "pch.h"
#include "Mesh.h"
#include "Renderer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Guava
{
	std::string ModelFolder = "D:/dev/Guava/Guava/src/Guava/Graphics/Models/";

	const Buffer::Layout Vertex::Layout = {
		Buffer::Attribute::Type::Vec3f,
		Buffer::Attribute::Type::Vec3f,
	};

	Mesh* Mesh::Create(const std::string_view meshFile)
	{
		return Renderer::CreateMesh(meshFile);
	}

	Mesh::Mesh(const std::string_view meshFile)
	{
		Assimp::Importer importer;
		auto path = ModelFolder + meshFile.data();

		const aiScene* scene = importer.ReadFile(path, 
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		GUAVA_ASSERT(scene != nullptr, importer.GetErrorString());

		m_Vertices.reserve(scene->mMeshes[0]->mNumVertices);
		m_Indices.reserve((size_t)scene->mMeshes[0]->mNumFaces * 3);

		for (unsigned int i = 0; i < scene->mMeshes[0]->mNumVertices; ++i)
		{
			Vertex vertex;
			auto aiVertex = scene->mMeshes[0]->mVertices[i];

			vertex.Position = { aiVertex.x , aiVertex.y , aiVertex.z };
			vertex.Normal = glm::normalize(vertex.Position); // Only works for spheres...

			m_Vertices.emplace_back(vertex);
		}

		for (unsigned int i = 0; i < scene->mMeshes[0]->mNumFaces; ++i)
		{
			m_Indices.emplace_back(scene->mMeshes[0]->mFaces[i].mIndices[0]);
			m_Indices.emplace_back(scene->mMeshes[0]->mFaces[i].mIndices[1]);
			m_Indices.emplace_back(scene->mMeshes[0]->mFaces[i].mIndices[2]);
		}
	}
}
