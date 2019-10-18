#include <Guava.h>

class Sandbox : public Guava::Application
{
public:

	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Guava::Application* Guava::CreateApplication()
{
	return new Sandbox();
}
