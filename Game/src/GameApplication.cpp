#include <SheeEngine.h>
#include <iostream>

class GameLayerEvent : public SheeEngine::Layer
{
public:
	GameLayerEvent() : Layer("GameLayerEvent") {};

	virtual void Update() override
	{
		APPLICATION_LOG_INFO("GameLayer:Event --- Update");
	}

	virtual void OnEvent(SheeEngine::Event& event) override
	{
		APPLICATION_LOG_INFO("GameLayer:Event --- Handle Event {0}", event.GetDetail());
	}

	virtual void OnPushInLayerStack()
	{
		APPLICATION_LOG_INFO("GameLayer:Event push in Stack");
	}
	virtual void OnRemoveFromLayerStack()
	{
		APPLICATION_LOG_INFO("GameLayer:Event Remove from Stack");
	}


private:

};

class GameLayerRender : public SheeEngine::Layer
{
public:
	GameLayerRender() : Layer("GameLayerRender") {};

	virtual void Update() override
	{
		APPLICATION_LOG_INFO("GameLayer:Render --- Update");
	}

	virtual void OnEvent(SheeEngine::Event& event) override
	{
		APPLICATION_LOG_INFO("GameLayer:Render --- Handle Event {0}", event.GetDetail());
	}

	virtual void OnPushInLayerStack()
	{
		APPLICATION_LOG_INFO("GameLayer:Render push in Stack");
	}
	virtual void OnRemoveFromLayerStack()
	{
		APPLICATION_LOG_INFO("GameLayer:Render Remove from Stack");
	}


private:

};


class GameApplication : public SheeEngine::Application
{
public:
	GameApplication()
	{
		LayerStackPush(new GameLayerRender());
		LayerStackPush(new GameLayerEvent());
	}

	~GameApplication()
	{

	}
};


SheeEngine::Application* SheeEngine::CreateApplication()
{
	return new GameApplication();
}

