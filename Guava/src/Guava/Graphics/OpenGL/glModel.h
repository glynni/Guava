#pragma once
#include "../Model.h"
#include "glVertexArray.h"
#include "glBuffer.h"

namespace Guava::OpenGL
{
	class glModel : public Model
	{
	public:

		glModel(const std::string_view filePath);

		void Draw() const override;

	private:

		glVertexArray	m_VertexArray;
		glVertexBuffer	m_VertexBuffer;
		glIndexBuffer	m_IndexBuffer;
	};
}

