#pragma once
#include "BufferLayout.h"
#include "Texture.h"

namespace Guava
{
	struct Vertex;
	struct Mesh;
	struct Material;

	using MeshBuffer =		std::vector<Mesh>;
	using VertexBuffer =	std::vector<Vertex>;
	using IndexBuffer =		std::vector<unsigned int>;
	using MaterialBuffer =  std::vector<Material>;

	class Model
	{
	public:

		virtual ~Model() = default;
		virtual void Draw() const = 0;

		static Model* Create(const StringView filePath);

	protected:

		Model(const StringView filePath);

		MeshBuffer		m_Meshes;
		VertexBuffer	m_Vertices;
		IndexBuffer		m_Indices;
		MaterialBuffer	m_Materials;

	private:

		// Assimp loading
		void LoadModel_Assimp(const StringView filePath);
		void LoadMesh_Assimp(const aiMesh* mesh);
		void LoadMaterials_Assimp(const aiScene* scene, const StringView filePath);
		
		// Custom .obj loading
		void LoadModel_OBJ(const StringView filePath);

		void ReserveMemory(size_t numMeshes, size_t numVertices, size_t numIndices, size_t numMaterials);
	};

	struct Vertex
	{
		glm::vec3	Position;
		glm::vec3	Normal;
		glm::vec2	UV_Coords;

		static const Buffer::Layout Layout;
	};

	struct Mesh
	{
		size_t BaseVertex = 0;
		size_t NumIndices = 0;

		unsigned int MaterialIndex;
	};

	struct Material
	{
		Texture* Diffuse = nullptr;
	};
}

