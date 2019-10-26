#include "pch.h"
#include "Mesh.h"
#include "Guava/Platform/OpenGL/OpenGLMesh.h"
#include "Renderer.h"

namespace Guava
{
	Mesh* Mesh::Create(const std::vector<Vertex3D>& mesh_data, const std::vector<unsigned int>& index_data)
	{
		Mesh* mesh = nullptr;

		switch (Renderer::GetAPI())
		{
			case RenderAPI::OpenGL:
			{
				if (index_data.size() > 0)
					mesh = new OpenGLMesh(mesh_data, index_data);
				else
					mesh = new OpenGLMesh(mesh_data);
			}
			break;

			default: GUAVA_INVALID_RENDER_API("Mesh");
		}

		if (mesh)
			Renderer::AddMesh(mesh);

		return mesh;
	}
}
