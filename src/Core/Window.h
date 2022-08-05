#pragma once
#include "seafx.h"
#include "Core/Core.h"
#include "Events/Event.h"

namespace SheeEngine
{
	struct WindowConfig
	{
		unsigned int Width;
		unsigned int Height;
		std::string WindowName;

		WindowConfig(unsigned int width = 1280, unsigned int height = 720, std::string name = "Shee Engine")
			: Width(width), Height(height), WindowName(name)
		{
		}
	};

	class SENGINE_API Window
	{
	public:
		using EventFunc = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void Update() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventFunc& eventfunc) = 0;

		virtual void SetVSync(bool value) = 0;

		static Window* Create(const WindowConfig& config = WindowConfig());

		virtual void* GetNativeWindow() const = 0;

	private:
		
	};


}