#include <SheeEngine.h>

class GameApplication : public SheeEngine::Application
{
public:
	GameApplication()
	{

	}

	~GameApplication()
	{

	}
};

SheeEngine::Application* SheeEngine::CreateApplication()
{
	return new GameApplication();
}