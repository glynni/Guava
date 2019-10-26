#pragma once
#include "Guava/Renderer/Mesh.h"

namespace Guava
{
	class OpenGLMesh : public Mesh
	{
	public:

		OpenGLMesh(const std::vector<Vertex3D>& mesh_data);
		OpenGLMesh(const std::vector<Vertex3D>& mesh_data, const std::vector<unsigned int>& index_data);

		~OpenGLMesh();

		void Draw() override;
		void DrawInstances(const std::vector<Instance3D>& instances) override;

	private:

		GLuint m_VertexArray, m_VertexBuffer, m_IndexBuffer, m_InstanceBuffer;

		GLsizei m_NumVertices;
		GLsizei m_NumIndices;

		void GenerateBuffers();
		void DeleteBuffers();
		void BindVertexArray();
		void SetVertexData(const std::vector<Vertex3D>& vertex_data);
		void SetIndexData(const std::vector<unsigned int>& index_data);
		void SetInstanceData(const std::vector<Instance3D>& instances);
		void SetupBufferLayouts();
	};
}

