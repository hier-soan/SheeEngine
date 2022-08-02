#pragma once
#include "Event.h"
#include "Core/Core.h"
#include <sstream>

namespace SheeEngine
{
	class SENGINE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
		virtual ~WindowResizeEvent() {}

		static EventType GetStaticEventType() { return EventType::WindowResize; }
		virtual EventType GetEventType() override { return GetStaticEventType(); }
		virtual std::string GetDetail() override
		{
			std::stringstream ss;
			ss << "Event - Window Resize: " << m_Width << "," << m_Height;
			return ss.str();
		};

		inline unsigned int GetWidth() { return m_Width; }
		inline unsigned int GetHeight() { return m_Height; }

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		
	};

	class SENGINE_API WindowCloseEvent : public Event
	{
	public:
		virtual ~WindowCloseEvent() {};

		static EventType GetStaticEventType() { return EventType::WindowClose; }
		virtual EventType GetEventType() override { return GetStaticEventType(); }
		virtual std::string GetDetail() override 
		{ 
			std::stringstream ss;
			ss << "Event - Window Close";
			return ss.str();
		}

	private:
	};
}