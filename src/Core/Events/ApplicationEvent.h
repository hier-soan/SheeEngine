#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace SheeEngine
{
	class ApplicationUpdateEvent : public Event
	{
	public:
		virtual ~ApplicationUpdateEvent() {}

		static EventType GetStaticEventType() { return EventType::ApplicationUpdate; };
		virtual EventType GetEventType() override { return GetStaticEventType(); };
		virtual std::string GetDetail() override { return "ApplicationUpdate"; };

	private:
	};

	class ApplicationRenderEvent : public Event
	{
	public:
		virtual ~ApplicationRenderEvent() {}

		static EventType GetStaticEventType() { return EventType::ApplicationRender; };
		virtual EventType GetEventType() override { return GetStaticEventType(); };
		virtual std::string GetDetail() override { return "ApplicationRender"; };

	private:
	};
}