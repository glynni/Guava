#pragma once
#include "Guava/Core/Transform.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Shader.h"

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

		// State changing
		static void ClearScreen();
		static void RenderFrame();
		static void SetClearColor(const Color& color);
		static void SetWindowSize(const glm::uvec2& size);
		static void SetViewport(const glm::uvec2& size, const glm::uvec2& bottomLeft = { 0, 0 });
		static void SetDrawMode(const PolygonMode drawMode);

		// Draw
		static void Draw(const Model* model, Shader* shader, Transform& transform, Camera& camera);
		static void Draw(const Light& light, Shader* shader);

		// Create Assets
		static Texture* CreateTexture(const StringView file, const TextureCreationInfo& description);
		static Model*	CreateModel(const StringView filePath);
		static Shader*	CreateShader(const StringView name);

	protected:

		Renderer();

		virtual void ClearScreen_Impl() = 0;
		virtual void SetViewport_Impl(const glm::uvec2& size, const glm::uvec2& bottomLeft) = 0;
		virtual void SetClearColor_Impl(const Color& color) = 0;
		virtual void SetDrawMode_Impl(const PolygonMode pm) = 0;
	};
}

