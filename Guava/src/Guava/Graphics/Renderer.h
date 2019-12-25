#pragma once
#include "Guava/Core/Transform.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"

namespace Guava
{
	enum class RenderAPI
	{
		OpenGL
	};

	enum class FillMode
	{
		Polygon,
		Wireframe
	};

	class Renderer
	{
	public:

		virtual ~Renderer() = default;

		static void Create(RenderAPI api);
		static void Destroy();

		// State changing
		static void ClearScreen();
		static void RenderFrame();
		static void SetClearColor(const Color& color);
		static void SetWindowSize(const uvec2& size);
		static void SetViewport(const uvec2& size, const uvec2& bottomLeft = { 0, 0 });
		static void SetFillMode(const FillMode drawMode);
		static void SetCamera(Camera& camera);

		// Draw
		static void Draw(Model* model, Transform& transform);
		static void Draw(Model* model, vector<Transform>& transforms);
		static void PointLight(const vec3& lightPos, const Color& lightColor, const float intensity);


	protected:

		Renderer() = default;

		virtual void ClearScreen_Impl() = 0;
		virtual void SetViewport_Impl(const uvec2& size, const uvec2& bottomLeft) = 0;
		virtual void SetClearColor_Impl(const Color& color) = 0;
		virtual void SetDrawMode_Impl(const FillMode pm) = 0;

		virtual Model*		CreateModel_Impl() = 0;
		virtual Texture2D*	CreateTexture_Impl(const Texture2DCreateInfo& tci) = 0;
		virtual Shader*		CreateShader_Impl() = 0;

	private:

		friend Texture2D;
		friend Shader;
		friend Model;

		static Model*	CreateModel();
		static Texture2D*	CreateTexture(const Texture2DCreateInfo& tci);
		static Shader*	CreateShader();
	};
}

