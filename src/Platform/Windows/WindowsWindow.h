#pragma once
#include "Core/Window.h"
#include "GLFW/glfw3.h"

namespace SheeEngine
{
	class SENGINE_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowConfig& config);
		virtual ~WindowsWindow();

		virtual void Update() override;

		inline virtual unsigned int GetWidth() const override { return m_WindowInfo.Width; };
		inline virtual unsigned int GetHeight() const override { return m_WindowInfo.Height; };

		virtual void SetEventCallback(const EventFunc& eventfunc) override { m_WindowInfo.EventCallback = eventfunc; }

		virtual void SetVSync(bool value) override;


		void Init();

		virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		// 集中数据的同时方便后面lambda表达式的书写
		struct WindowInfo
		{
			std::string Name;
			unsigned int Width;
			unsigned int Height;

			EventFunc EventCallback;

			WindowInfo(unsigned int width, unsigned int height, std::string name) : Width(width), Height(height), Name(name) {}
		};
		WindowInfo m_WindowInfo;

		bool bVSync;

		GLFWwindow* m_Window;
	};
}

