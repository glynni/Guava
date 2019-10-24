#pragma once
#include "Guava/Renderer/Mesh.h"

#include <glad/glad.h>

namespace Guava
{
	class OpenGLMesh : public Mesh
	{
	public:

		OpenGLMesh(const std::vector<Vertex3D>& mesh_data);
		OpenGLMesh(const std::vector<Vertex3D>& mesh_data, const std::vector<unsigned int>& index_data);

		~OpenGLMesh();

		void Draw();

	private:

		GLuint m_VertexArray, m_VertexBuffer, m_IndexBuffer, m_InstanceBuffer;

		GLsizei m_NumVertices;
		GLsizei m_NumIndices;

		void GenerateBuffers();
		void DeleteBuffers();
		void SetVertexData(const std::vector<Vertex3D>& vertex_data);
		void SetIndexData(const std::vector<unsigned int>& index_data);
		void SetupBufferLayouts();
	};
}

