#pragma once

#include <MeshComponentFactory.h>
#include <GuiManager.h>
#include "RenderSystem.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"

class Editor {
public:

	Editor(bool&, const GuiManager&);

	void OnUpdate(float deltaTime);
	void OnRender();
	void OnImGuiRender();

	GuiManager gui_manager;
private:
	bool& editor_mode;
//	GLFWwindow* window;
	Manager m;
	MeshComponentFactory mesh_factory;
	RenderSystem render_system;
	Entity sphere1;
};
