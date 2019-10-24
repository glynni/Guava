#include "Mesh.h"
#include "Guava/Platform/OpenGL/OpenGLMesh.h"
#include "Renderer.h"
#include "Guava/Log.h"

namespace Guava
{
	Mesh* Mesh::Create(const std::vector<Vertex3D>& mesh_data)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::OpenGL: return new OpenGLMesh(mesh_data);

		default: GUAVA_INVALID_RENDER_API("Mesh");
		}

		return nullptr;
	}

	Mesh* Mesh::Create(const std::vector<Vertex3D>& mesh_data, const std::vector<unsigned int>& index_data)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::OpenGL: return new OpenGLMesh(mesh_data, index_data);

		default: GUAVA_INVALID_RENDER_API("Mesh");
		}

		return nullptr;
	}

	/*Mesh* Mesh::Create(const aiMesh* ai_mesh);
	{
		auto api = Renderer::GetAPI();

		switch (api)
		{
		case RenderAPI::OpenGL: return new OpenGLMesh(mesh_data, index_data);

		default: INVALID_API();
		}
	}*/
}
