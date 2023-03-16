
#include <Prokaryotic.h>

class Sandbox : public PROKARYOTIC::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

PROKARYOTIC::Application* PROKARYOTIC::Create_application()
{
	return new Sandbox();
}