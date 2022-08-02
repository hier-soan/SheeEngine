#include "seafx.h"
#include "WindowsWindow.h"
#include "Core/Events/WindowEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyboardEvent.h"

namespace SheeEngine
{
	Window* Window::Create(const WindowConfig& config)
	{
		return new WindowsWindow(config);
	}

	WindowsWindow::WindowsWindow(const WindowConfig& config)
		: m_WindowInfo(config.Width, config.Height, config.WindowName)
	{
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
	}

	bool b_GLFWInitialized = false;
	void WindowsWindow::Init()
	{
		SENGINE_LOG_INFO("Create Window Name:{0}, (W, H):({1}, {2})", m_WindowInfo.Name, m_WindowInfo.Width, m_WindowInfo.Height);
		if (!b_GLFWInitialized)
		{
			int success = glfwInit();

			SENGINE_CORE_ASSERT(!success, "Could not init GLFW");

			b_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow(m_WindowInfo.Width, m_WindowInfo.Height, m_WindowInfo.Name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_WindowInfo);  // 暂时存储窗口数据

		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				auto info = (WindowInfo*)glfwGetWindowUserPointer(window);
				info->Width = width;
				info->Height = height;
				
				WindowResizeEvent windowResizeEvent(info->Width, info->Height);
				info->EventCallback(windowResizeEvent);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				auto info = (WindowInfo*)glfwGetWindowUserPointer(window);
				MouseMoveEvent mouseMoveEvent(xpos, ypos);
				info->EventCallback(mouseMoveEvent);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				auto info = (WindowInfo*)glfwGetWindowUserPointer(window);
				WindowCloseEvent windowCloseEvent;
				info->EventCallback(windowCloseEvent); 
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				auto info = (WindowInfo*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent mouseScrolledEvent(xoffset, yoffset);
				info->EventCallback(mouseScrolledEvent);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto info = (WindowInfo*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MousePressEvent mousePressEvent(button, action);
					info->EventCallback(mousePressEvent);
				}break;
				case GLFW_RELEASE:
				{
					MouseReleaseEvent mouseReleaseEvent(button, action);
					info->EventCallback(mouseReleaseEvent);
				}break;
				default:
					break;
				}
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto info = (WindowInfo*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyboardPressEvent keyPressEvent(key, scancode, action);
					info->EventCallback(keyPressEvent);
				}break;
				case GLFW_RELEASE:
				{
					KeyboardReleaseEvent keyReleaseEvent(key, scancode, action);
					info->EventCallback(keyReleaseEvent);
				}break;
				case GLFW_REPEAT:
				{
					KeyboardPressEvent keyPressEvent(key, scancode, action);
					info->EventCallback(keyPressEvent);
				}break;
				default:
					break;
				}
			});
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool value)
	{
		if (value)
		{
			glfwSwapInterval(1);   // wait for a frame
		}
		else
		{
			glfwSwapInterval(0);
		}
		bVSync = value;
	}
}