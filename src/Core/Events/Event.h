#pragma once
#include "Core/Core.h"
#include <string>
#include <unordered_map>

namespace SheeEngine
{
	enum class EventType
	{
		null = 0,
		WindowResize, WindowMove, WindowClose,
		KeyBoardPress, KeyBoardRelease,
		MouseMove, MousePress, MouseRelease, MouseScroll,
		ApplicationUpdate, ApplicationRender
	};

	class SENGINE_API Event
	{
	public:
		friend class EventDispatcher;

		virtual ~Event() {};

		static EventType GetStaticEventType();    // ¥Ê¥¢¿‡

		virtual EventType GetEventType() = 0;
		virtual std::string GetDetail() = 0;

	private:
		bool bHandle;
	};

	class EventDispatcher
	{
		template<typename T>
		using EvenDispatchFunc = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		~EventDispatcher() {}


		template<typename T>
		void Dispatch(EvenDispatchFunc<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticEventType())
			{
				m_Event.bHandle = func(*(T*)&m_Event);
			}
		}
	private:
		Event& m_Event;
	};
}