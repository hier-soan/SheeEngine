#include "seafx.h"
#include "Application.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace SheeEngine
{
	Application* Application::m_Instance = nullptr;

	Application::Application() : bIsRunning(true)
	{
		m_Instance = this;

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
			glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : m_ApplicationLayerStack)
			{
				layer->Update();
			}

			// swapbuffer must at last
			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& event)
	{
		// imgui didn't bind WindowCloseEvent with Callback, we should bind ourselves;
		EventDispatcher dispacther(event);
		dispacther.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

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
		layer->OnPushInLayerStack();
	}

	void Application::LayerStackRemove(Layer* layer)
	{
		m_ApplicationLayerStack.PopLayer(layer);
		layer->OnRemoveFromLayerStack();
	}

	void Application::SuperstratumPush(Layer* layer)
	{
		m_ApplicationLayerStack.PushSuperstratumLayer(layer);
		layer->OnPushInLayerStack();
	}

	void Application::SuperstratumRemove(Layer* layer)
	{
		m_ApplicationLayerStack.PopSuperstratumLayer(layer);
		layer->OnRemoveFromLayerStack();
	}
}
