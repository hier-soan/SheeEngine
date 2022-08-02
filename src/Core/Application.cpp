#include "seafx.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace SheeEngine
{
	Application::Application() : bIsRunning(true)
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		auto BindFunc = std::bind(&Application::OnEvent, this, std::placeholders::_1);
		m_Window->SetEventCallback(BindFunc);
	}

	Application::~Application()
	{

	}

	void Application::Update()
	{
		while (bIsRunning)
		{
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->Update();


			for (auto layer : m_ApplicationLayerStack)
			{
				layer->Update();
			}
		}
	}

	void Application::OnEvent(Event& event)
	{
		//SENGINE_LOG_INFO("{0}", event.GetDetail());

		EventDispatcher dispacther(event);
		dispacther.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	//	dispacther.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
	//	dispacther.Dispatch<MouseMoveEvent>(std::bind(&Application::OnMouseMove, this, std::placeholders::_1));
	//	dispacther.Dispatch<MousePressEvent>(std::bind(&Application::OnMousePress, this, std::placeholders::_1));
	//	dispacther.Dispatch<MouseReleaseEvent>(std::bind(&Application::OnMouseRelease, this, std::placeholders::_1));
	//	dispacther.Dispatch<MouseScrolledEvent>(std::bind(&Application::OnMouseScrolled, this, std::placeholders::_1));
	//	dispacther.Dispatch<KeyboardPressEvent>(std::bind(&Application::OnKeyboardPress, this, std::placeholders::_1));
	//	dispacther.Dispatch<KeyboardReleaseEvent>(std::bind(&Application::OnKeyboardRelease, this, std::placeholders::_1));

		for (auto it = m_ApplicationLayerStack.end(); it != m_ApplicationLayerStack.begin(); )
		{
			// should decline first because it = .end() at the beginning, or will crash
			(*--it)->OnEvent(event);
			if (event.GetHandleStatus())
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		bIsRunning = false;
		std::cout << event.GetDetail() << std::endl;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		std::cout << event.GetHeight() << "," << event.GetWidth() << std::endl;
		return true;
	}

	bool Application::OnMouseMove(MouseMoveEvent& event)
	{
		std::cout << event.GetXOffset() << "," << event.GetYOffset() << std::endl;
		return true;
	}

	bool Application::OnMousePress(MousePressEvent& event)
	{
		std::cout << event.GetAction() << "," << event.GetButton() << std::endl;
		return true;
	}

	bool Application::OnMouseRelease(MouseReleaseEvent& event)
	{
		std::cout << event.GetAction() << "," << event.GetButton() << std::endl;
		return true;
	}

	bool Application::OnMouseScrolled(MouseScrolledEvent& event)
	{
		std::cout << event.GetXOffset() << "," << event.GetYOffset() << std::endl;
		return true;
	}

	bool Application::OnKeyboardPress(KeyboardPressEvent& event)
	{
		std::cout << event.GetAction() << "," << event.GetKey() << std::endl;
		return true;
	}

	bool Application::OnKeyboardRelease(KeyboardReleaseEvent& event)
	{
		std::cout << event.GetAction() << "," << event.GetKey() << std::endl;
		return true;
	}

	void Application::LayerStackPush(Layer* layer)
	{
		m_ApplicationLayerStack.PushLayer(layer);
	}

	void Application::LayerStackRemove(Layer* layer)
	{
		m_ApplicationLayerStack.PopLayer(layer);
	}
}
