#include "pch.h"
#include "glMesh.h"

namespace Guava::OpenGL
{
	glMesh::glMesh(const std::string_view meshFile) : Mesh(meshFile)
	{
		m_VertexArray.Bind();

		m_VertexBuffer.SetData(m_Vertices.data(), sizeof(Vertex), m_Vertices.size());
		m_VertexBuffer.SetLayout(Vertex::Layout);

		m_IndexBuffer.SetData(m_Indices.data(), sizeof(unsigned int), m_Indices.size());

		// Free Memory
		m_Vertices = std::vector<Vertex>();
		m_Indices = std::vector<unsigned int>();
	}

	void glMesh::Draw()
	{
		m_VertexArray.Bind();
		m_IndexBuffer.Bind();

		glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetElementCount(), GL_UNSIGNED_INT, nullptr);
	}
}
