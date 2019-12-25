#pragma once
#include "../Model.h"
#include "glVertexArray.h"
#include "glBuffer.h"

namespace Guava::OpenGL
{
	class glModel : public Model
	{
	public:

		glModel() = default;

		void Draw(Shader* shader, const vector<ModelInstance>& instances) override;

	private:

		scope<glVertexArray>	m_VertexArray;
		scope<glVertexBuffer>	m_VertexBuffer;
		scope<glIndexBuffer>	m_IndexBuffer;
		scope<glInstanceBuffer>	m_InstanceBuffer;
		bool					m_Initialized;

		void UpdateGPU() override;
	};
}

