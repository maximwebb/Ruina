#pragma once

#include <MeshComponentFactory.h>
#include <GuiManager.h>
#include "RenderSystem.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"
#include "Scene.h"

class Editor {
public:

	Editor(bool& editor_mode, const GuiManager&, GLFWwindow*);

	void OnUpdate(float deltaTime);
	void OnRender();
	void OnImGuiRender();

	GuiManager gui_manager;
private:
	bool& editor_mode;
	Manager m;
	Scene scene;
};
