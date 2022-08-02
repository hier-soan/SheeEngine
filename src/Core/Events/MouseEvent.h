#pragma once
#include "Event.h"
#include <sstream>

namespace SheeEngine
{
	class SENGINE_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(int x, int y) : m_xPos(x), m_yPos(y) {}

		static EventType GetStaticEventType() { return EventType::MouseMove; };

		virtual EventType GetEventType() override { return GetStaticEventType(); };
		virtual std::string GetDetail() override 
		{
			std::stringstream ss;
			ss << "Event - Mouse Pos (x, y) :" << m_xPos << "," << m_yPos;
			return ss.str();
		}

		inline unsigned int GetXOffset() const { return m_xPos; }
		inline unsigned int GetYOffset() const { return m_yPos; }


	private:
		unsigned int m_xPos;
		unsigned int m_yPos;
	};

	class SENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int x, int y) : m_xOffset(x), m_yOffset(y) {}

		static EventType GetStaticEventType() { return EventType::MouseMove; };

		virtual EventType GetEventType() override { return GetStaticEventType(); };
		virtual std::string GetDetail() override
		{
			std::stringstream ss;
			ss << "Event - Mouse Scrolled Offset (x, y) :" << m_xOffset << "," << m_yOffset;
			return ss.str();
		}

		inline unsigned int GetXOffset() const { return m_xOffset; }
		inline unsigned int GetYOffset() const { return m_yOffset; }


	private:
		unsigned int m_xOffset;
		unsigned int m_yOffset;
	};

	class SENGINE_API MousePressEvent : public Event
	{
	public:
		MousePressEvent(unsigned int button, unsigned int action) : m_button(button), m_action(action) {}

		static EventType GetStaticEventType() { return EventType::MousePress; };

		virtual EventType GetEventType() override { return GetStaticEventType(); };
		virtual std::string GetDetail() override
		{
			std::stringstream ss;
			ss << "Event - Mouse Press - " << "Button" << m_button;
			return ss.str();
		}

		inline unsigned int GetButton() const { return m_button; }
		inline unsigned int GetAction() const { return m_action; }

	private:
		unsigned int m_button;
		unsigned int m_action;
	};

	class SENGINE_API MouseReleaseEvent : public Event
	{
	public:
		MouseReleaseEvent(unsigned int button, unsigned int action) : m_button(button), m_action(action) {}

		static EventType GetStaticEventType() { return EventType::MouseRelease; };

		virtual EventType GetEventType() override { return GetStaticEventType(); };
		virtual std::string GetDetail() override
		{
			std::stringstream ss;
			ss << "Event - Mouse Release - " << "Button" << m_button;
			return ss.str();
		}

		inline unsigned int GetButton() const { return m_button; }
		inline unsigned int GetAction() const { return m_action; }

	private:
		unsigned int m_button;
		unsigned int m_action;
	};
}