#pragma once
#include "Core/Core.h"
#include "Core/Events/Event.h"
#include <iostream>

namespace SheeEngine
{
	class SENGINE_API Layer
	{
	public:
		Layer(std::string name = "DefaultLayer");
		virtual ~Layer();

		virtual void OnPushInLayerStack() = 0;
		virtual void OnRemoveFromLayerStack() = 0;

		virtual void Update() = 0;
		virtual void OnEvent(Event& event) = 0;

	private:
		std::string m_LayerName;
	};
}

