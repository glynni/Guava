#pragma once
#include "Mesh.h"
#include "Shader.h"

#include <memory>
#include <unordered_map>

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
		static void Draw(Mesh* mesh, Shader* shader, const Instance3D& instance);
		static void Draw(Mesh* mesh, Shader* shader, const std::vector<Instance3D>& instances);
		static void RenderFrame();

		static void AddMesh(Mesh* mesh);
		static void AddShader(Shader* shader);

		static const RenderAPI GetAPI();

	protected:

		Renderer();

		virtual void ClearScreen_Impl() = 0;

		static RenderAPI s_RenderAPI;

		// All render specific data is held by the renderer and destroyed with it
		typedef std::unordered_map<Mesh*, std::unique_ptr<Mesh>> MeshMap;
		typedef std::unordered_map<Shader*, std::unique_ptr<Shader>> ShaderMap;
		typedef std::unordered_map<Shader*, std::unordered_map<Mesh*, std::vector<Instance3D>>> RenderGraph;

		MeshMap m_Meshes;
		ShaderMap m_Shaders;

		RenderGraph m_RenderGraph;

	private:

		static std::unique_ptr<Renderer> s_Instance;
	};
}

