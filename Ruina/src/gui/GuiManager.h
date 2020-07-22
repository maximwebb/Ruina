#pragma once

#include <vector>
#include <iterator>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "IGuiElement.h"

class GuiManager {
private:
	GLFWwindow* m_window;
	std::vector<IGuiElement*> m_gui_elements;
	int m_count;
public:
	GuiManager(GLFWwindow* window);
	~GuiManager();
	void Begin(const char* title);
	void Render();
	void AddGuiElement(IGuiElement*);
	void AddGuiElement(IGuiElement*, bool);
	void DrawGuiElements();
};