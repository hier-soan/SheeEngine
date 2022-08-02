#pragma once
#include "Core/Window.h"
#include "Core/Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"
#include <iostream>

namespace SheeEngine
{
	class SENGINE_API Application
	{
	public:
	  	Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& event);
		
		bool OnWindowClose(WindowCloseEvent& event);

		bool OnWindowResize(WindowResizeEvent& event);

		bool OnMouseMove(MouseMoveEvent& event);

		bool OnMousePress(MousePressEvent& event);

		bool OnMouseRelease(MouseReleaseEvent& event);

		bool OnMouseScrolled(MouseScrolledEvent& event);

		bool OnKeyboardPress(KeyboardPressEvent& event);

		bool OnKeyboardRelease(KeyboardReleaseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool bIsRunning;
	};

	Application* CreateApplication();
}


