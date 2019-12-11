#pragma once
#include "../Mesh.h"
#include "glVertexArray.h"
#include "glBuffer.h"

namespace Guava::OpenGL
{
	class glMesh : public Mesh
	{
	public:

		glMesh(const aiMesh* mesh);

		void Draw() override;

	private:

		glVertexArray	m_VertexArray;
		glVertexBuffer	m_VertexBuffer;
		glIndexBuffer	m_IndexBuffer;
	};
}

