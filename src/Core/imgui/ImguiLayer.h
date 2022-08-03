#pragma once
#include "Core/Layer/Layer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "imgui/imgui_internal.h"

#include <stdio.h>

namespace SheeEngine
{
	class SENGINE_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnPushInLayerStack() override;
		virtual void OnRemoveFromLayerStack() override;

		virtual void Update() override;
		virtual void OnEvent(Event& event) override;

	private:
		float m_Time = 0.0f;
	};
}

