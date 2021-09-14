#include "Editor.h"
#include <GL/glew.h>
#include <MotionComponent.h>


Editor::Editor(bool& editor_mode, const GuiManager& gui_manager) :
	editor_mode(editor_mode), m({}), mesh_factory(m), gui_manager(gui_manager), render_system(m), sphere1(m.Create()) {
	glm::mat4 model1 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(10.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(5.0f, 5.0f, 5.0f)),
				glm::vec3(-0.5f, -1.5f, 0.0f));

		glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(-3.0f, -0.5f, 0.0f));
		mesh_factory.CreateSphereMesh(sphere1, model1, 10);
};

void Editor::OnUpdate(float deltaTime) {
	m.QueueEvent<GameTickEvent>({});
}

void Editor::OnRender() {
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m.QueueEvent<RenderEvent>({});
}

void Editor::OnImGuiRender() {
	if (ImGui::Button("Editor Mode", {100, 50})) {
		std::cout << "blah" << std::endl;
	}
}
