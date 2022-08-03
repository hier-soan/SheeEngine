#include "seafx.h"
#include "ImguiLayer.h"
#include "Core/Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include <GLFW/glfw3.h>

namespace SheeEngine
{
	ImguiLayer::ImguiLayer() : Layer("Imgui Layer")
	{
		
	}

	ImguiLayer::~ImguiLayer()
	{
	}

	void ImguiLayer::OnPushInLayerStack()
	{
		SENGINE_LOG_INFO("Imgui is push in stack");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplGlfw_InitForOpenGL(WindowsWindow::GetGLFWwindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}

	void ImguiLayer::OnRemoveFromLayerStack()
	{
	}

	void ImguiLayer::Update()
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::OnEvent(Event& event)
	{
	}

}
