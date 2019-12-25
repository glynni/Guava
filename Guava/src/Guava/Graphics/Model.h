#pragma once
#include "Guava/Graphics/BufferLayout.h"
#include "Texture2D.h"
#include "Shader.h"

namespace Guava
{
	struct ModelVertex;
	struct ModelMesh;
	struct ModelInstance;
	class Material;

	class Model
	{
	public:

		virtual ~Model() = default;
		virtual void Draw(Shader* shader, const vector<ModelInstance>& instances) = 0;

		static Model* LoadFromData(const vector<ModelVertex>& vb, const vector<unsigned int>& ib, Material* mtl = nullptr);
		static Model* LoadFromFile(const string_view path);

	protected:

		vector<ModelMesh>		m_Meshes;
		vector<ModelVertex>		m_Vertices;
		vector<unsigned int>	m_Indices;

		Model() = default;

		void FreeData();
		virtual void UpdateGPU() = 0;

	private:

		// Assimp loading
		bool LoadModel_Assimp(const string_view filePath);
		void LoadMesh_Assimp(const aiMesh* mesh, vector<Material*>& materials);

		void ReserveMemory(size_t numMeshes, size_t numVertices, size_t numIndices);
	};

	struct ModelVertex
	{
		ModelVertex(
			const vec3& p = vec3(), 
			const vec3& n = vec3(),
			const vec3& t = vec3(),
			const vec3& b = vec3(),
			const vec2& uv = vec2()) :

			Position(p),
			Normal(n),
			Tangent(t),
			Bitangent(b),
			UV_Coords(uv)
		{}

		vec3 Position;
		vec3 Normal;
		vec3 Tangent;
		vec3 Bitangent;
		vec2 UV_Coords;

		static const Buffer::Layout Layout;
	};

	struct ModelInstance
	{
		mat4 ModelMatrix;

		static const Buffer::Layout Layout;
	};

	struct ModelMesh
	{
		size_t BaseVertex = 0;
		size_t NumIndices = 0;
		size_t IndexOffset = 0;
		Material* Mat;
	};
}

