#pragma once
#include <memory>

namespace Guava
{
	enum class RenderAPI
	{
		None, 
		OpenGL,
		DirectX12,
		Vulkan
	};

	class Renderer
	{
	public:

		virtual ~Renderer() {};

		static void Create(RenderAPI api);
		static void Destroy();
		static void ClearScreen();

		static const RenderAPI GetAPI();

	protected:

		Renderer() {}

		virtual void Clear() = 0;

		static RenderAPI s_RenderAPI;

	private:

		static std::unique_ptr<Renderer> m_Renderer;
	};
}

