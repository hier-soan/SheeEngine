#include "seafx.h"
#include "Core/Log.h"
#include "LayerStack.h"

namespace SheeEngine
{
	LayerStack::LayerStack() : m_HaveUpperLayer(false)
	{
		m_UpperLayerIterator = m_LayerStack.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_LayerStack)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it == m_LayerStack.end())
		{
			m_LayerStack.emplace_back(layer);
		}
		else
		{
			SENGINE_LOG_WARN("This Layer is already in Stack !");
		}
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end())
		{
			m_LayerStack.erase(it);
			SENGINE_LOG_INFO("Erase this Layer Successfully !");
		}
		else
		{
			SENGINE_LOG_WARN("Without this Layer !");
		}
	}

	void LayerStack::PushSuperstratumLayer(Layer* superstratum)
	{
		if (!m_HaveUpperLayer)
		{
			m_UpperLayerIterator = m_LayerStack.emplace(m_UpperLayerIterator, superstratum);
			m_HaveUpperLayer = true;
		}
		
	}

	void LayerStack::PopSuperstratumLayer(Layer* superstratum)
	{
		if (m_HaveUpperLayer)
		{
			m_LayerStack.erase(m_UpperLayerIterator);
		}
	}

}