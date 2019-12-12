#include "pch.h"
#include "Mesh.h"
#include "Renderer.h"

namespace Guava
{
	const Buffer::Layout Vertex::Layout = {
		Buffer::Attribute::Type::Vec3f,
		Buffer::Attribute::Type::Vec3f
	};

	Mesh* Mesh::Create(const aiMesh* mesh)
	{
		return Renderer::CreateMesh(mesh);
	}

	Mesh::Mesh(const aiMesh* mesh)
	{
		m_Vertices.reserve(mesh->mNumVertices);
		m_Indices.reserve((size_t)mesh->mNumFaces * 3);

		// Position, Normal, Color
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;

			aiVector3D& aiVertex = mesh->mVertices[i];
			vertex.Position = { aiVertex.x , aiVertex.y , aiVertex.z };

			// Normals
			if (mesh->HasNormals())
			{
				aiVector3D& aiNormal = mesh->mNormals[i];
				vertex.Normal = { aiNormal.x , aiNormal.y , aiNormal.z };
			}
			else
			{
				// Only works for spheres... 
				// assimp-generated normals are ugly, or I don't understand something fundamental
				//vertex.Normal = glm::normalize(vertex.Position);
			}

			m_Vertices.emplace_back(vertex);
		}

		// Indices
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
				m_Indices.emplace_back(mesh->mFaces[i].mIndices[j]);
		}
	}
}
