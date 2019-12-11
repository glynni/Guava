#pragma once
#include "BufferLayout.h"

namespace Guava
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;

		static const Buffer::Layout Layout;
	};

	class Mesh
	{
	public:

		virtual ~Mesh() = default;
		virtual void Draw() = 0;
		
		static Mesh* Create(const std::string_view meshFile);

	protected:

		Mesh(const std::string_view meshFile);

		std::vector<Vertex>			m_Vertices;
		std::vector<unsigned int>	m_Indices;
	};
}

