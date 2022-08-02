#pragma once
#include "Core/Window.h"
#include "Core/Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/LayerStack.h"
#include <iostream>

namespace SheeEngine
{
	class SENGINE_API Application
	{
	public:
	  	Application();

		virtual ~Application();

		void Update();

		void OnEvent(Event& event);
		
		bool OnWindowClose(WindowCloseEvent& event);

		bool OnWindowResize(WindowResizeEvent& event);

		bool OnMouseMove(MouseMoveEvent& event);

		bool OnMousePress(MousePressEvent& event);

		bool OnMouseRelease(MouseReleaseEvent& event);

		bool OnMouseScrolled(MouseScrolledEvent& event);

		bool OnKeyboardPress(KeyboardPressEvent& event);

		bool OnKeyboardRelease(KeyboardReleaseEvent& event);

		void LayerStackPush(Layer* layer);

		void LayerStackRemove(Layer* layer);

	private:
		std::unique_ptr<Window> m_Window;
		bool bIsRunning;

		LayerStack m_ApplicationLayerStack;
	};

	Application* CreateApplication();
}


