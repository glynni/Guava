#include "pch.h"
#include "Model.h"
#include "Material.h"
#include "Guava/Core/ResourceManager.h"
#include "Guava/Graphics/Renderer.h"

namespace Guava
{
	const Buffer::Layout ModelVertex::Layout = {
		Buffer::Attribute::Type::Vec3f, // Pos
		Buffer::Attribute::Type::Vec3f, // Normal
		Buffer::Attribute::Type::Vec3f, // Tangent
		Buffer::Attribute::Type::Vec3f, // Bitangent
		Buffer::Attribute::Type::Vec2f  // UV
	};

	const Buffer::Layout ModelInstance::Layout = {
		Buffer::Attribute::Type::Mat4f // ModelMatrix
	};

	Model* Model::LoadFromData(const vector<ModelVertex>& vb, const vector<unsigned int>& ib, Material* mtl)
	{
		if (vb.empty())
			return nullptr;

		Model* m = Renderer::CreateModel();

		m->m_Vertices = vb;
		m->m_Indices = ib;

		auto& mesh = m->m_Meshes.emplace_back();
		mesh.NumIndices = ib.size();
		mesh.Mat = mtl;

		ResourceManager::RegisterModel(m);

		return m;
	}

	Model* Model::LoadFromFile(const string_view path)
	{
		Model* m = ResourceManager::GetModel(path);

		if (m) return m;

		m = Renderer::CreateModel();

		if (!m->LoadModel_Assimp(path))
		{
			delete m;
			return nullptr;
		}

		ResourceManager::RegisterModel(m, path);

		return m;
	}

	void Model::FreeData()
	{
		m_Vertices = vector<ModelVertex>();
		m_Indices = vector<unsigned int>();
	}

	bool Model::LoadModel_Assimp(const string_view filePath)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filePath.data(),
			aiProcess_GenSmoothNormals |
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices
		);

		GUAVA_ASSERT(scene != nullptr, string("Model could not be loaded: ") + filePath.data());

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

		ReserveMemory(numMeshes, numVertices, numIndices);

		// Materials
		auto materials = Material::LoadAll(filePath, scene);

		// Meshes
		numIndices = 0;
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			if (mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			{
				GUAVA_WARN("{0} in {1} was not loaded: Unsupported primitive types", mesh->mName.C_Str(), filePath.data());
				continue;
			}

			LoadMesh_Assimp(mesh, materials);
		}

		// Sort Meshes by material index to reduce shader calls
		std::sort(m_Meshes.begin(), m_Meshes.end(), [](ModelMesh& m1, ModelMesh& m2)
		{
			return m1.Mat < m2.Mat;
		});

		return true;
	}

	void Model::LoadMesh_Assimp(const aiMesh* mesh, vector<Material*>& materials)
	{
		ModelMesh& newMesh = m_Meshes.emplace_back();
		newMesh.BaseVertex = m_Vertices.size();
		newMesh.NumIndices = 0;
		newMesh.Mat = materials[mesh->mMaterialIndex];

		// Position, Normal, Tangent, Bitangent, UV
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			ModelVertex vertex;

			// Position
			aiVector3D& aiVertex = mesh->mVertices[i];
			vertex.Position.x = aiVertex.x;
			vertex.Position.y = aiVertex.y;
			vertex.Position.z = aiVertex.z;

			// Normals
			if (mesh->HasNormals())
			{
				aiVector3D& aiNormal = mesh->mNormals[i];
				vertex.Normal.x = aiNormal.x;
				vertex.Normal.y = aiNormal.y;
				vertex.Normal.z = aiNormal.z;
			}

			// Tangents & Bitangents
			if (mesh->HasTangentsAndBitangents())
			{
				aiVector3D& bitangent = mesh->mBitangents[i];
				vertex.Bitangent.x = bitangent.x;
				vertex.Bitangent.y = bitangent.y;
				vertex.Bitangent.z = bitangent.z;

				aiVector3D& tangent = mesh->mTangents[i];
				vertex.Tangent.x = tangent.x;
				vertex.Tangent.y = tangent.y;
				vertex.Tangent.z = tangent.z;

				// Fix for symmetric models ?
				//if(dot(cross(vertex.Normal, vertex.Tangent), vertex.Bitangent) < 0.0f)
					//vertex.Tangent = vertex.Tangent * -1.0f;
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
			newMesh.NumIndices += mesh->mFaces[i].mNumIndices;

			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
			{
				m_Indices.emplace_back(mesh->mFaces[i].mIndices[j]);
			}
		}

		size_t numMeshes = m_Meshes.size();
		if (numMeshes > 1)
		{
			auto& mesh = m_Meshes[numMeshes - 1];
			auto& prevMesh = m_Meshes[numMeshes - 2];

			mesh.IndexOffset = prevMesh.NumIndices + prevMesh.IndexOffset;
		}
	}

	void Model::ReserveMemory(size_t numMeshes, size_t numVertices, size_t numIndices)
	{
		m_Meshes = vector<ModelMesh>();
		m_Vertices = vector<ModelVertex>();
		m_Indices = vector<unsigned int>();

		m_Meshes.reserve(numMeshes);
		m_Vertices.reserve(numVertices);
		m_Indices.reserve(numIndices);
	}

	/*void Model::LoadModel_OBJ(const string_view filePath)
	{
		using namespace File;

		TextFile file(filePath);

		if (!file.IsEmpty())
		{
			SubstringBuffer splitLine, splitFace;
			auto& lines = file.ExtractLines();

			constexpr size_t res = 20000;
			vector<vec3> positions;
			vector<vec3> normals;
			vector<vec2> uvs;
			positions.reserve(res);
			normals.reserve(res);
			uvs.reserve(res);
			m_Indices.reserve(res * 3);
			m_Vertices.reserve(res);

			size_t indexOffset = 0, indexStart = 0;
			Mesh* currentMesh = nullptr;
			string buf1, buf2, buf3;

			for (auto& line : lines)
			{
				SplitString(line, ' ', splitLine);

				if (!splitLine.empty())
				{
					if ('o' == splitLine[0][0])
					{
						// mesh
						if (currentMesh)
						{
							currentMesh->NumIndices = m_Indices.size() - indexStart;
							indexStart = m_Indices.size();
						}

						currentMesh = &m_Meshes.emplace_back();
						currentMesh->BaseVertex = positions.size();
						currentMesh->Name = splitLine[1];
						indexOffset = positions.size();
					}
					else if ('v' == splitLine[0][0])
					{
						// vertex
						buf1 = splitLine[1];
						buf2 = splitLine[2];
						buf3 = splitLine[3];
						positions.emplace_back(
							stof(buf1),
							stof(buf2),
							stof(buf3));
					}
					else if ("vn" == splitLine[0])
					{
						// normal
						buf1 = splitLine[1];
						buf2 = splitLine[2];
						buf3 = splitLine[3];
						normals.emplace_back(normalize(vec3(
							stof(buf1),
							stof(buf2),
							stof(buf3))));
					}
					else if ("vt" == splitLine[0])
					{
						// uv
						buf1 = splitLine[1];
						buf2 = splitLine[2];
						uvs.emplace_back(
							stof(buf1),
							stof(buf2));
					}
					else if ('f' == splitLine[0][0])
					{
						// faces
						size_t posIndex, uvIndex, normalIndex;
						SubstringBuffer splitFace;

						for (unsigned int i = 1; i <= 3; ++i)
						{
							SplitString(splitLine[i], '/', splitFace);

							buf1 = splitFace[0];
							buf2 = splitFace[1];
							buf3 = splitFace[2];

							posIndex =		(size_t)stoi(buf1) - 1;
							uvIndex =		(size_t)stoi(buf2) - 1;
							normalIndex =	(size_t)stoi(buf3) - 1;

							m_Indices.emplace_back(posIndex - indexOffset);

							if (posIndex >= m_Vertices.size())
							{
								m_Vertices.emplace_back(
									positions[posIndex],
									normals[normalIndex],
									uvs[uvIndex]);
							}
						}
					}
					else if ("mtllib" == splitLine[0])
					{
						// material file
					}
				}
			}

			// process last mesh
			if (currentMesh)
				currentMesh->NumIndices = m_Indices.size() - indexStart;
		}
	}
	*/
}
