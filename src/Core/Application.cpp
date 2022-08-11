#include "seafx.h"
#include "Application.h"
#include "glfw/glfw3.h"
#include "Render/Render.h"

#include <filesystem>

namespace SheeEngine
{
	Application* Application::m_Instance = nullptr;

	Application::Application() : bIsRunning(true)
	{
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		auto BindFunc = std::bind(&Application::OnEvent, this, std::placeholders::_1);
		m_Window->SetEventCallback(BindFunc);

		// test
		InitSquare();
	}

	Application::~Application()
	{

	}

	void Application::Update()
	{
		while (bIsRunning)
		{
			RenderStaticLib::SetBasicColor(0.45f, 0.55f, 0.60f, 1.00f);

			// test
			RenderSquare();

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


	// Custom Event System
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



	/**
	*
	* Test
	*
	*/


	float squareVertices[] = {
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    // top right
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f    // top left 
	};

	unsigned int squareIndices[] = {
			 0, 1, 3,  // first Triangle
			 1, 2, 3   // second Triangle
	};

	void Application::InitSquare()
	{
		std::vector<VertexAttribute> v_layout;
		v_layout.push_back(VertexAttribute(0, "Position", AttributeType::Postion));
		v_layout.push_back(VertexAttribute(1, "Color", AttributeType::Color));

		VertexBufferLayout bufferLayout(v_layout);

		m_VAO.reset(new VertexArray());
		m_VAO->Bind();

		m_VAO->SetVBO(squareVertices, sizeof(squareVertices), bufferLayout);
		m_VAO->SetEBO(squareIndices, sizeof(squareIndices));
	}

	void Application::RenderSquare()
	{
		std::shared_ptr<Shader> squareShader = 
		std::make_shared<Shader>("D:/GameCode/SheeEngine/src/Core/GLSL/ver_square.glsl", 
				"D:/GameCode/SheeEngine/src/Core/GLSL//fra_square.glsl");

		RenderStaticLib::Draw(squareShader, m_VAO);
	}
}
