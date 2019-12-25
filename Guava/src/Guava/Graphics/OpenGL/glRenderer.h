#pragma once
#include "Guava/Graphics/Renderer.h"
#include "glShader.h"
#include "glBuffer.h"
#include "glVertexArray.h"
#include "glTexture2D.h"
#include "glModel.h"

namespace Guava::OpenGL
{
	class glRenderer : public Guava::Renderer
	{
	public:

		glRenderer();
		~glRenderer();

		void ClearScreen_Impl() override;
		void SetViewport_Impl(const uvec2& size, const uvec2& bottomLeft) override;
		void SetClearColor_Impl(const Color& color) override;
		void SetDrawMode_Impl(const FillMode drawMode) override;

		Model* CreateModel_Impl();
		Texture2D* CreateTexture_Impl(const Texture2DCreateInfo& tci);
		Shader* CreateShader_Impl();

	private:

		void Prepare();
	};
}

