#include <SheeEngine.h>
#include <iostream>

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

