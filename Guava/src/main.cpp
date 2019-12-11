#include "pch.h"
#include "Guava/Core/Window.h"
#include "Guava/Graphics/Renderer.h"

using namespace Guava;

int main()
{
	Logger::Create();
	Window::Create("", 800, 600);
	Renderer::Create(RenderAPI::OpenGL);
	Renderer::SetClearColor(Color(0.8f, 0.8f, 0.8f, 1.0f));

	Shader::Files meshShader;
	meshShader.VertexShader		= "mesh_vertex.glsl";
	meshShader.FragmentShader	= "mesh_fragment.glsl";

	Mesh*		sphere = Mesh::Create("sphere.nff");
	Shader*		shader = Shader::Create(meshShader);
	Camera		camera;
	Transform	transform;

	transform.SetPosition({0, 0, -10.f});
	camera.SetPosition({0.0f, 0.0f, 0.0f});

	while (!Window::ShouldClose())
	{
		Window::PollEvents();

		camera.MoveUpwards();
		camera.Update(0.000005f);

		Renderer::ClearScreen();
		Renderer::Draw(sphere, shader, transform, camera);

		Window::Present();
	}

	Renderer::Destroy();
	Window::Destroy();

	std::cin.get();
}
