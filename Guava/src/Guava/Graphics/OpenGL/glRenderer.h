#pragma once
#include "Guava/Graphics/Renderer.h"
#include "glShader.h"
#include "glBuffer.h"
#include "glVertexArray.h"
#include "glTexture.h"

namespace Guava::OpenGL
{
	class glRenderer : public Guava::Renderer
	{
	public:

		glRenderer();
		~glRenderer();

		void ClearScreen_Impl() override;
		void SetViewport_Impl(const glm::uvec2& size, const glm::uvec2& bottomLeft) override;
		void SetClearColor_Impl(const Color& color) override;
		void SetDrawMode_Impl(const PolygonMode drawMode) override;

	private:

		void Prepare();
	};
}

