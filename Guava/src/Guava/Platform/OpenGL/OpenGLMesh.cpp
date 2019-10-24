#include "OpenGLMesh.h"

namespace Guava
{
	OpenGLMesh::OpenGLMesh(const std::vector<Vertex3D>& mesh_data) : 
		m_NumVertices(mesh_data.size()), m_NumIndices(0)
	{																 
		GenerateBuffers();

		glBindVertexArray(m_VertexArray);
		SetVertexData(mesh_data);
		SetupBufferLayouts();
		glBindVertexArray(0);
	}

	OpenGLMesh::OpenGLMesh(const std::vector<Vertex3D>& mesh_data, const std::vector<unsigned int>& index_data) : 
		m_NumVertices(mesh_data.size()), m_NumIndices(index_data.size())
	{
		GenerateBuffers();

		glBindVertexArray(m_VertexArray);

		SetVertexData(mesh_data);
		SetupBufferLayouts();
		SetIndexData(index_data);

		glBindVertexArray(0);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		DeleteBuffers();
	}

	void OpenGLMesh::Draw()
	{
		glBindVertexArray(m_VertexArray);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		if (m_NumIndices > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, nullptr);
		}
		else
			glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);
	}

	void OpenGLMesh::DrawInstances(const std::vector<Instance3D>& instances)
	{
		glBindVertexArray(m_VertexArray);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		SetInstanceData(instances);

		if (m_NumIndices > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			glDrawElementsInstanced(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, nullptr, instances.size());
		}
		else
			glDrawArraysInstanced(GL_TRIANGLES, 0, m_NumVertices, instances.size());
	}

	void OpenGLMesh::GenerateBuffers()
	{
		glGenVertexArrays(1, &m_VertexArray);
		glGenBuffers(1, &m_VertexBuffer);
		glGenBuffers(1, &m_IndexBuffer);
		glGenBuffers(1, &m_InstanceBuffer);
	}
	void OpenGLMesh::DeleteBuffers()
	{
		glDeleteVertexArrays(1, &m_VertexArray);
		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteBuffers(1, &m_IndexBuffer);
		glDeleteBuffers(1, &m_InstanceBuffer);
	}
	void OpenGLMesh::SetVertexData(const std::vector<Vertex3D>& vertex_data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(Vertex3D), vertex_data.data(), GL_STATIC_DRAW);
		
	}
	void OpenGLMesh::SetIndexData(const std::vector<unsigned int>& index_data)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndices * sizeof(unsigned int), index_data.data(), GL_STATIC_DRAW);
	}

	void OpenGLMesh::SetInstanceData(const std::vector<Instance3D>& instances)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(Instance3D), instances.data(), GL_DYNAMIC_DRAW);
	}

	void OpenGLMesh::SetupBufferLayouts()
	{
		// Vertex Data (Vetex3D)
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

		// Instance data (matrix)
		glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBuffer);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0 * sizeof(glm::vec4)));
		glVertexAttribDivisor(3, 1);				    	   
													    	   
		glEnableVertexAttribArray(4);				    	   
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
		glVertexAttribDivisor(4, 1);				    	   
													    	   
		glEnableVertexAttribArray(5);				    	   
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glVertexAttribDivisor(5, 1);				    	   
													    	   
		glEnableVertexAttribArray(6);				    	   
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(6, 1);
	}
}