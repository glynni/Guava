#include "pch.h"
#include "Guava/Platform/OpenGL/OpenGLRenderer.h"

namespace Guava
{
	RenderAPI Renderer::s_RenderAPI = RenderAPI::OpenGL;
	std::unique_ptr<Renderer> Renderer::s_Instance;

	void Renderer::Create(RenderAPI api)
	{
		Destroy();

		switch (api)
		{

		case RenderAPI::OpenGL:
		{
			s_Instance = std::make_unique<OpenGLRenderer>();
		}
		break;

		default:
			GUAVA_INVALID_RENDER_API("Renderer");
		}

		s_RenderAPI = api;
	}

	void Renderer::Destroy()
	{
		s_Instance.reset();
	}

	void Renderer::ClearScreen()
	{
		s_Instance->ClearScreen_Impl();
	}

	void Renderer::Draw(Mesh* mesh, Shader* shader, const Instance3D& instance)
	{
		s_Instance->m_RenderGraph[shader][mesh].emplace_back(instance);
	}

	void Renderer::Draw(Mesh* mesh, Shader* shader, const std::vector<Instance3D>& instances)
	{
		auto& inst = s_Instance->m_RenderGraph[shader][mesh];

		inst.insert(inst.end(), instances.begin(), instances.end());
	}

	void Renderer::RenderFrame()
	{
		auto& graph = s_Instance->m_RenderGraph;

		for (auto& shaderToMesh : graph)
		{
			// Bind the shader
			shaderToMesh.first->Use();

			for (auto& meshToInstances : shaderToMesh.second)
			{
				// Reference to model-matrices
				auto& instances = meshToInstances.second;

				if (!instances.empty())
				{
					// Draw mesh for given instances
					meshToInstances.first->DrawInstances(instances);
					meshToInstances.second.clear();
				}
			}
		}
	}

	void Renderer::AddMesh(Mesh* mesh)
	{
		auto& meshes = s_Instance->m_Meshes;

		auto it =  std::find_if(meshes.begin(), meshes.end(), [&](auto& m) -> bool 
		{
			return m.first == mesh;
		});

		if (it == meshes.end())
		{
			meshes.emplace(mesh, mesh);
		}
		else
			GUAVA_CORE_TRACE("Mesh {0} was already added to renderer.", (void*)mesh);
	}

	void Renderer::AddShader(Shader* shader)
	{
		auto& shaders = s_Instance->m_Shaders;

		auto it = std::find_if(shaders.begin(), shaders.end(), [&](auto& s) -> bool
		{
			return s.first == shader;
		});

		if (it == shaders.end())
		{
			shaders.emplace(shader, shader);
		}
		else
			GUAVA_CORE_TRACE("Shader {0} was already added to renderer.", (void*)shader);
	}

	const RenderAPI Renderer::GetAPI()
	{
		return s_RenderAPI;
	}
	
	Renderer::Renderer()
	{

	}
}
