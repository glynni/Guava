#include "pch.h"
#include "glModel.h"

namespace Guava::OpenGL
{
	glModel::glModel(const std::string_view filePath) : Model(filePath)
	{
		m_VertexArray.Bind();

		m_VertexBuffer.SetData(m_Vertices.data(), sizeof(Vertex), m_Vertices.size());
		m_VertexBuffer.SetLayout(Vertex::Layout);

		m_IndexBuffer.SetData(m_Indices.data(), sizeof(unsigned int), m_Indices.size());

		// Free Memory
		m_Vertices = VertexBuffer();
		m_Indices = IndexBuffer();
	}

	void glModel::Draw() const
	{
		m_VertexArray.Bind();
		m_IndexBuffer.Bind();

		size_t byteOffset = 0;

		for (auto& mesh : m_Meshes)
		{
			Texture* diffuse = m_Materials[mesh.MaterialIndex].Diffuse;

			if(diffuse)
				diffuse->Bind();
			else
			{
				int a = 3;
			}

			glDrawElementsBaseVertex(
				GL_TRIANGLES, 
				mesh.NumIndices, 
				GL_UNSIGNED_INT, 
				(void*)byteOffset,
				mesh.BaseVertex);

			byteOffset += (mesh.NumIndices * sizeof(unsigned int));
		}
	}
}
