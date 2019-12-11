#pragma once
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Guava/Core/Transform.h"

namespace Guava
{
	struct RendererData;

	enum class RenderAPI
	{
		OpenGL
	};

	class Renderer
	{
	public:

		virtual ~Renderer();

		static void Create(RenderAPI api);
		static void Destroy();

		static void ClearScreen();
		static void SetClearColor(const Color& color);

		// Draw
		static void Draw(Mesh* mesh, Shader* shader, const Transform& transform, const Camera& camera);

		// Create Assets
		static Texture* CreateTexture(const Texture::Description& description, const std::string_view filePath);
		static Mesh* CreateMesh(const std::string_view filePath);
		static Shader* CreateShader(const Shader::Files& files);
		static Shader* CreateShader(const Shader::Code& code);
		
		// Resize the viewport
		static void SetViewport(const glm::uvec2 & size, const glm::uvec2& bottomLeft = { 0, 0 });

	protected:

		Renderer();

		virtual void ClearScreen_Impl() = 0;
		virtual void SetViewport_Impl(const glm::uvec2& size, const glm::uvec2& bottomLeft) = 0;
		virtual void SetClearColor_Impl(const Color& color) = 0;

		// Structuring of passed drawables
		std::unique_ptr<RendererData> m_Data;
	};
}

