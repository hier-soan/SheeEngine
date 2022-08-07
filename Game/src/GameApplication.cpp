#include <SheeEngine.h>
#include <iostream>

class GameApplication : public SheeEngine::Application
{
public:
	GameApplication()
	{
		SuperstratumPush(new SheeEngine::ImguiLayer());
		
	}

	~GameApplication()
	{

	}
};


SheeEngine::Application* SheeEngine::CreateApplication()
{
	return new GameApplication();
}

