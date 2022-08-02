#pragma once
#include "Core/Core.h"
#include "Layer.h"
#include <vector>

namespace SheeEngine
{
	class SENGINE_API LayerStack
	{
		using Layer_Iterator = std::vector<Layer*>::iterator;
		using Layer_Stack = std::vector<Layer*>;

	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushSuperstratumLayer(Layer* superstratum);
		void PopSuperstratumLayer(Layer* superstratum);

		Layer_Iterator begin() { return m_LayerStack.begin(); }
		Layer_Iterator end() { return  m_LayerStack.end(); }

	private:
		Layer_Iterator m_UpperLayerIterator;
		Layer_Stack m_LayerStack;

		bool m_HaveUpperLayer;
	};
}
