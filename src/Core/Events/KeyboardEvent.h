#pragma once
#include "Event.h"
#include <sstream>

namespace SheeEngine
{
	class SENGINE_API KeyboardPressEvent : public Event
	{
	public:
		KeyboardPressEvent(unsigned int key, unsigned int scancode, unsigned int action)
			: m_key(key), m_scancode(scancode), m_action(action)
		{}

		static EventType GetStaticEventType() { return EventType::KeyBoardPress; }

		virtual EventType GetEventType() { return GetStaticEventType(); }
		virtual std::string GetDetail()
		{
			std::stringstream ss;
			ss << "Event - Key Press : key:" << m_key << ", scancode:" << m_scancode;
			if (m_action == 2)
				ss << " - statue: Repeat";
			return ss.str();
		}

		unsigned int GetKey() const { return m_key; }
		unsigned int GetScancode() const { return m_scancode; }
		unsigned int GetAction() const { return m_action; }

	private:
		unsigned int m_key;
		unsigned int m_scancode;
		unsigned int m_action;
	};

	class SENGINE_API KeyboardReleaseEvent : public Event
	{
	public:
		KeyboardReleaseEvent(unsigned int key, unsigned int scancode, unsigned int action)
			: m_key(key), m_scancode(scancode), m_action(action)
		{}

		static EventType GetStaticEventType() { return EventType::KeyBoardPress; }

		virtual EventType GetEventType() { return GetStaticEventType(); }
		virtual std::string GetDetail()
		{
			std::stringstream ss;
			ss << "Event - Key Release : key:" << m_key << ", scancode:" << m_scancode;
			return ss.str();
		}

		unsigned int GetKey() const { return m_key; }
		unsigned int GetScancode() const { return m_scancode; }
		unsigned int GetAction() const { return m_action; }

	private:
		unsigned int m_key;
		unsigned int m_scancode;
		unsigned int m_action;
	};
}
