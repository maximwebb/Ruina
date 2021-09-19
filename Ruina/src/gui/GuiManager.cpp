#include <GL/glew.h>
#include "GuiManager.h"

GuiManager::GuiManager(GLFWwindow* window)
	: m_window(window),  m_gui_elements(std::vector<IGuiElement*>()) {
	IMGUI_CHECKVERSION();
	ctx = ImGui::CreateContext();
	ImGui::SetCurrentContext(ctx);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

GuiManager::~GuiManager() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GuiManager::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GuiManager::Begin(const char* title, ImVec2 pos) {
	ImGui::Begin(title);
	ImGui::SetWindowPos(pos, ImGuiCond_Once);
}

void GuiManager::Begin(const char* title) {
	ImGui::Begin(title);
}

void GuiManager::End() {
	ImGui::End();
}

void GuiManager::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
