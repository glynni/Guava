#pragma once
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Guava/Core/Transform.h"

namespace Guava
{
	enum class RenderAPI
	{
		OpenGL
	};

	enum class PolygonMode
	{
		Fill,
		Wireframe
	};

	class Renderer
	{
	public:

		virtual ~Renderer();

		static void Create(RenderAPI api);
		static void Destroy();

		// State changing & single operations
		static void ClearScreen();
		static void BeginFrame();
		static void EndFrame();
		static void SetClearColor(const Color& color);
		static void SetWindowSize(const glm::uvec2& size);
		static void SetViewport(const glm::uvec2& size, const glm::uvec2& bottomLeft = { 0, 0 });
		static void SetDrawMode(const PolygonMode drawMode);

		// Draw
		static void Draw(Mesh* mesh, Shader* shader, const Transform& transform, const Camera& camera);

		// Create Assets
		static Texture* CreateTexture(const std::string_view file, const Texture::Description& description);
		static Mesh* CreateMesh(const aiMesh* mesh);
		static Shader* CreateShader(const std::string_view name);

	protected:

		Renderer();

		virtual void ClearScreen_Impl() = 0;
		virtual void SetViewport_Impl(const glm::uvec2& size, const glm::uvec2& bottomLeft) = 0;
		virtual void SetClearColor_Impl(const Color& color) = 0;
		virtual void SetDrawMode_Impl(const PolygonMode pm) = 0;
	};
}

