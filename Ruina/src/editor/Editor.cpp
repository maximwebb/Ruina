#include "Editor.h"
#include <GL/glew.h>


Editor::Editor(bool& editor_mode, const GuiManager& gui_manager, GLFWwindow* window) :
	editor_mode(editor_mode), m({}), gui_manager(gui_manager), scene(window) {}

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
	gui_manager.End();

	gui_manager.Begin("Second", {50, 250});
	if (ImGui::Button("Forwards")) {
		scene.ChangePosition(0.3);
		std::cout << "Forwards" << std::endl;
	}
	if (ImGui::Button("Backwards")) {
		scene.ChangePosition(-0.3);
		std::cout << "Backwards" << std::endl;
	}
	gui_manager.End();
	gui_manager.Render();
}
