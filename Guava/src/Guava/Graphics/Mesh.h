#pragma once
#include "BufferLayout.h"

namespace Guava
{
	struct Vertex
	{
		glm::vec3	Position;
		glm::vec3	Normal;

		static const Buffer::Layout Layout;
	};

	class Mesh
	{
	public:

		virtual ~Mesh() = default;
		virtual void Draw() const = 0;
		
		static Mesh* Create(const aiMesh* mesh);

	protected:

		Mesh(const aiMesh* mesh);

		std::vector<Vertex>			m_Vertices;
		std::vector<unsigned int>	m_Indices;
	};
}

