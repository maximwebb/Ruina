#include <GL/glew.h>
#include "GuiManager.h"

GuiManager::GuiManager(GLFWwindow* window)
	: m_window(window),  m_gui_elements(std::vector<IGuiElement*>()) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

GuiManager::~GuiManager() {

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GuiManager::Begin(const char* title) {
	ImGui::Begin(title);
}

void GuiManager::Render() {
	DrawGuiElements();
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::DrawGuiElements() {
	for (IGuiElement* element : m_gui_elements) {
		element->Draw();
	}
}

/* Inserts newline by default */
void GuiManager::AddGuiElement(IGuiElement* element) {
	m_gui_elements.push_back(element);
}

/* For specifying whether a newline is inserted or not */
class GuiSameLine : public IGuiElement {
public:
	inline void Draw() override { ImGui::SameLine(); };
};

void GuiManager::AddGuiElement(IGuiElement* element, bool newline) {
	m_gui_elements.push_back(element);
	if (newline) {
		auto* same_line = new GuiSameLine();
		m_gui_elements.push_back(same_line);
	}
}


