#include <Guava.h>

class Sandbox : public Guava::Application
{
public:

	Sandbox()
	{
		GUAVA_CLIENT_ERROR("Error message from the client! Error code: {0}", 1337);
	}

	~Sandbox()
	{

	}
};

Guava::Application* Guava::CreateApplication()
{
	return new Sandbox();
}
