#include "Editor.h"
#include <GL/glew.h>

Editor::Editor(bool& editor_mode, const GuiManager& gui_manager, GLFWwindow* window) :
	editor_mode(editor_mode), m({}), gui_manager(gui_manager), scene(window, gui_manager) {

}

void Editor::OnUpdate(float deltaTime) {
	scene.OnUpdate(deltaTime);
}

void Editor::OnRender() {
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	scene.OnRender();
}

void Editor::OnImGuiRender() {
	gui_manager.Begin("Editor", {50, 50});
	if (ImGui::Button("<-")) {
		editor_mode = false;
	}
	scene.OnImGuiRender();
	gui_manager.End();
	gui_manager.Render();
}
