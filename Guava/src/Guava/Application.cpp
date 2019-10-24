#include "Application.h"
#include "Log.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "File.h"

namespace Guava
{
	Application::Application() : m_Window(Window::Create("Guava", 1280, 720))
	{
		GUAVA_CORE_INFO("Created Guava-Application instance");
	}

	Application::~Application()
	{
		GUAVA_CORE_INFO("Terminated Guava-Application instance");
	}

	void Application::Run()
	{
		m_Window->EnableVSync(true);

		Renderer::Create(RenderAPI::OpenGL);

		std::vector<Vertex3D> vertices = {
			{vec3(-0.5f, -0.5f, 0.0f), vec2(), vec4()},
			{vec3( 0.5f, -0.5f, 0.0f), vec2(), vec4()},
			{vec3( 0.0f,  0.5f, 0.0f), vec2(), vec4()}
		};

		std::unique_ptr<Mesh> mesh(Mesh::Create(vertices));

		ShaderInput si;

		si.VertexShaderCode = File::ReadTextFile("files/shaders/basic_shader.vs");
		si.FragmentShaderCode = File::ReadTextFile("files/shaders/basic_shader.fs");

		std::unique_ptr<Shader> shader(Shader::Create(si));
		shader->Use();

		while (!m_Window->AwaitsClosing())
		{
			m_Window->Update();

			Renderer::ClearScreen();

			mesh->Draw();

			m_Window->PresentFrame();
		}

		Renderer::Destroy();
	}
}
