#pragma once
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Guava
{
	struct Vertex3D
	{
		Vertex3D() {}
		Vertex3D(const glm::vec3& pos, const glm::vec2& tc, const glm::vec4& col) :
			Position(pos), TextureCoordinates(tc), Color(col) {}

		glm::vec3 Position;
		glm::vec2 TextureCoordinates;
		glm::vec4 Color;
	};

	struct Instance3D
	{
		glm::mat4 ModelMatrix;
	};

	//struct aiMesh;

	class Mesh
	{
	public:

		static Mesh* Create(const std::vector<Vertex3D>& mesh_data);
		static Mesh* Create(const std::vector<Vertex3D>& mesh_data, const std::vector<unsigned int>& index_data);
		//static Mesh* Create(const aiMesh* ai_mesh);

		virtual ~Mesh() {};

		virtual void Draw() = 0;
		virtual void DrawInstances(const std::vector<Instance3D>& instances) = 0;
	};

}

