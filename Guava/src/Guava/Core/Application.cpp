#include "Application.h"
#include "Log.h"
#include "Guava/Renderer/Mesh.h"
#include "Guava/Renderer/Renderer.h"
#include "Guava/Renderer/Shader.h"
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
			{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
			{glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec2(), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},
			{glm::vec3( 1.0f,  1.0f, 0.0f), glm::vec2(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)},
			{glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec2(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}
		};

		std::vector<unsigned int> indices = {
			0, 2, 1, 
			0, 3, 2
		};

		std::vector<Instance3D> instances = {
			{glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,  0.5f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.25f, 1.0f))},
			{glm::translate(glm::mat4(1.0f), glm::vec3(0.5f,  0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(75.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.5f, 1.0f))},
			{glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(125.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 1.0f))}
		};

		std::unique_ptr<Mesh> mesh(Mesh::Create(vertices, indices));

		ShaderInput si;

		si.VertexShaderCode = File::ReadTextFile("files/shaders/basic_shader.vs");
		si.FragmentShaderCode = File::ReadTextFile("files/shaders/basic_shader.fs");

		std::unique_ptr<Shader> shader(Shader::Create(si));
		shader->Use();

		while (!m_Window->AwaitsClosing())
		{
			m_Window->Update();

			Renderer::ClearScreen();

			mesh->DrawInstances(instances);

			m_Window->PresentFrame();
		}

		Renderer::Destroy();
	}
}
