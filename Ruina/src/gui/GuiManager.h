#pragma once

#include <vector>
#include <iterator>
#include "imgui/imgui.h"
#include <imgui/imgui_internal.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "IGuiElement.h"

class GuiManager {
private:
	GLFWwindow* m_window;
	std::vector<IGuiElement*> m_gui_elements;
	ImGuiContext* ctx;
	int m_count;
public:
	GuiManager(GLFWwindow* window);
	~GuiManager();
	void NewFrame();
	void Begin(const char* title);
	void Begin(const char* title, ImVec2 pos);
	void End();
	void Render();
};