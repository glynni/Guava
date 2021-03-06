#include "pch.h"
#include "glModel.h"
#include "glTexture2D.h"
#include "../Material.h"

namespace Guava::OpenGL
{
	void glModel::Draw(Shader* shader, const vector<ModelInstance>& instances)
	{
		GPU_UpdateData();

		m_VertexArray->Bind();
		m_IndexBuffer->Bind();

		m_InstanceBuffer->SetData(instances.data(), sizeof(ModelInstance), instances.size());

		Material* prevMaterial = nullptr;

		for (auto& mesh : m_Meshes)
		{
			// Meshes are sorted by material, shader checks if new material should be applied
			shader->ApplyMaterial(mesh.Mat);

			glDrawElementsInstancedBaseVertex(
				GL_TRIANGLES,
				(GLsizei)mesh.NumIndices,
				GL_UNSIGNED_INT,
				(void*)(mesh.IndexOffset * sizeof(unsigned int)),
				(GLsizei)instances.size(),
				(GLint)mesh.BaseVertex);
		}
	}

	void glModel::GPU_UpdateData()
	{
		if (!m_Initialized)
		{
			m_VertexArray.reset(new glVertexArray());
			m_VertexBuffer.reset(new glVertexBuffer());
			m_IndexBuffer.reset(new glIndexBuffer());
			m_InstanceBuffer.reset(new glInstanceBuffer());

			m_VertexArray->Bind();

			m_VertexBuffer->SetData(m_Vertices.data(), sizeof(ModelVertex), m_Vertices.size());
			m_VertexBuffer->SetLayout(ModelVertex::Layout);

			m_InstanceBuffer->SetLayout(ModelInstance::Layout, m_VertexBuffer.get());

			m_IndexBuffer->SetData(m_Indices.data(), sizeof(unsigned int), m_Indices.size());

			FreeMemory();
			m_Initialized = true;
		}
	}
}
