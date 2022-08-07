#pragma once
#include "Core/Window.h"
#include "Core/Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Render/Buffer.h"
#include "Core/Render/Shader.h"

#include <iostream>

#include <memory>

//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
//#include <glm/gtc/constants.hpp> // glm::pi


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

		void SuperstratumPush(Layer* layer);

		void SuperstratumRemove(Layer* layer);


		inline static Application* GetInstance() { return m_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		bool bIsRunning;

		LayerStack m_ApplicationLayerStack;

		static Application* m_Instance;


		// buffer
		std::shared_ptr<VertexArray> m_VAO;


		void InitSquare();
		void RenderSquare();

	};

	Application* CreateApplication();
}


