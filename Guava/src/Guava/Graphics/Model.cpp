#include "pch.h"
#include "Model.h"
#include "Guava/Core/AssetManager.h"
#include "Guava/Core/Utility.h"

namespace Guava
{
	const Buffer::Layout Vertex::Layout = {
		Buffer::Attribute::Type::Vec3f,
		Buffer::Attribute::Type::Vec3f,
		Buffer::Attribute::Type::Vec2f
	};

	Model::Model(const std::string_view filePath)
	{
		std::string extension = GetFileExtension(filePath);

		LoadModel_Assimp(filePath);
	}

	Model* Model::Create(const std::string_view filePath)
	{
		return AssetManager::GetModel(filePath);
	}

	void Model::LoadModel_Assimp(const std::string_view filePath)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filePath.data(),
			aiProcess_GenNormals |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		GUAVA_ASSERT(scene != nullptr, std::string("Model could not be loaded: ") + filePath.data());

		// Reserve Memory
		size_t numVertices = 0;
		size_t numIndices = 0;
		size_t numMeshes = 0;

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			if (mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
				continue;

			numVertices += mesh->mNumVertices;
			numIndices += (size_t(mesh->mNumFaces) * 3);
			numMeshes++;
		}

		ReserveMemory(numMeshes, numVertices, numIndices, scene->mNumMeshes);

		// Meshes
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			if (mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			{
				GUAVA_CORE_WARN("{0} in {1} was not loaded: Unsupported primitive types", mesh->mName.C_Str(), filePath.data());
				continue;
			}

			LoadMesh_Assimp(mesh);
		}

		// Materials
		LoadMaterials_Assimp(scene, filePath);

		//GUAVA_CORE_TRACE(" meshes: {0}", m_Meshes.size());
		//GUAVA_CORE_TRACE(" vertices: {0}", m_Vertices.size());
		//GUAVA_CORE_TRACE(" indices: {0}", m_Indices.size());
		//GUAVA_CORE_TRACE(" materials: {0}", scene->mNumMaterials);
	}

	void Model::LoadMesh_Assimp(const aiMesh* mesh)
	{
		if (mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			return;

		Mesh& newMesh = m_Meshes.emplace_back();
		newMesh.BaseVertex = m_Vertices.size();
		newMesh.NumIndices = size_t(mesh->mNumFaces) * 3;
		newMesh.MaterialIndex = mesh->mMaterialIndex;

		// Position, Normal, UV
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;

			// Position
			aiVector3D& aiVertex = mesh->mVertices[i];
			vertex.Position.x = aiVertex.x;
			vertex.Position.y = aiVertex.y;
			vertex.Position.z = aiVertex.z;

			// Normals
			if (mesh->HasNormals())
			{
				aiVector3D& aiNormal = mesh->mNormals[i];
				vertex.Normal = glm::normalize(glm::vec3{ aiNormal.x , aiNormal.y , aiNormal.z });
			}

			// UV
			if (mesh->HasTextureCoords(0))
			{
				aiVector3D& uv = mesh->mTextureCoords[0][i];
				vertex.UV_Coords.x = uv.x;
				vertex.UV_Coords.y = uv.y;
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

	void Model::LoadMaterials_Assimp(const aiScene* scene, const std::string_view filePath)
	{
		std::string fileDir = GetFileDirectory(filePath);

		for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
		{
			aiMaterial* material = scene->mMaterials[i];
			Material& newMaterial = m_Materials.emplace_back();
			aiString diffuseTexture;

			if (AI_SUCCESS == material->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), diffuseTexture))
				newMaterial.Diffuse = Texture::Create(fileDir + diffuseTexture.C_Str());
		}
	}

	void Model::ReserveMemory(size_t numMeshes, size_t numVertices, size_t numIndices, size_t numMaterials)
	{
		m_Meshes = MeshBuffer();
		m_Vertices = VertexBuffer();
		m_Indices = IndexBuffer();
		m_Materials = MaterialBuffer();

		m_Meshes.reserve(numMeshes);
		m_Materials.reserve(numMaterials);
		m_Vertices.reserve(numVertices);
		m_Indices.reserve(numIndices);
	}
}
