#include "pch.h"
#include "Application.h"
#include "Guava/Renderer/Renderer.h"
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
		Renderer::Create(RenderAPI::OpenGL);

		std::vector<Vertex3D> vertices
		{
			{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
			{glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec2(), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},
			{glm::vec3( 1.0f,  1.0f, 0.0f), glm::vec2(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)},
			{glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec2(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}
		};

		std::vector<unsigned int> indices
		{
			0, 2, 1, 
			0, 3, 2
		};

		std::vector<Instance3D> instances
		{
			{glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,  0.5f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.25f, 1.0f))},
			{glm::translate(glm::mat4(1.0f), glm::vec3(0.5f,  0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(75.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.5f, 1.0f))},
			{glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(125.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 1.0f))}
		};

		Instance3D singleInstance{ glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(125.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 1.0f)) };

		ShaderFiles shaderInput
		{ 
			"files/shaders/basic_shader.vs",
			"files/shaders/basic_shader.fs"
		};

		Mesh* mesh = Mesh::Create(vertices, indices);
		Shader* shader = Shader::Create(shaderInput);

		m_Window->EnableVSync(true);

		while (!m_Window->AwaitsClosing())
		{
			m_Window->Update();

			Renderer::ClearScreen();
			Renderer::Draw(mesh, shader, instances);
			Renderer::Draw(mesh, shader, singleInstance);
			Renderer::RenderFrame();

			m_Window->PresentFrame();
		}

		Renderer::Destroy();
	}
}
