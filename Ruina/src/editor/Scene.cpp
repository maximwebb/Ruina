#include "Scene.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Scene::Scene(GLFWwindow* window) : m(), render_system(m), window(window), selected(-1), base_model(1.0f),
translation(0.0f) {
	AddCube();
	movement_system = std::make_unique<MovementSystem>(m, render_system.camera, window, 0.15f, 0.02f);
	object_selection_system = std::make_unique<ObjectSelectionSystem>(m, render_system.camera, window);
	window_event_system = std::make_unique<WindowEventSystem>(m, window);
	m.RegisterEventListener(typeid(SelectElementEvent), HANDLER(UpdateSelected));
}

void Scene::OnUpdate(float deltaTime) {
	m.QueueEvent<GameTickEvent>({});
}

void Scene::OnRender() {
	m.QueueEvent<RenderEvent>({});
}

void Scene::OnImGuiRender() {
	if (selected != -1) {
		ImGui::SliderFloat("x-axis", &translation.x, -5.0f, 5.0f);
		ImGui::SliderFloat("y-axis", &translation.y, -5.0f, 5.0f);
		ImGui::SliderFloat("z-axis", &translation.z, -5.0f, 5.0f);
		ChangePosition(-translation.x, translation.y, translation.z);
	}
}

void Scene::UpdateSelected(const Event& ev) {
	SelectElementEvent e = *(SelectElementEvent*) (&ev);
	if (e.clicked) {
		selected = e.id;
		if (selected != -1) {
			auto g = m.CreateGroup<MeshComponent>();
			auto[mesh] = g.Get(selected);
			base_model = mesh->model;
		}
		translation = glm::vec3(0.0f);
	}
}

void Scene::AddCube() {
	glm::mat4 model1 = glm::translate(
			glm::scale(
					glm::rotate(
							glm::mat4(10.0f),
							0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
					glm::vec3(5.0f, 5.0f, 5.0f)),
			glm::vec3(-0.5f, -1.5f, 0.0f));


	glm::mat4 model = glm::mat4(1.0f);
	Entity e = m.Create();
	m.Add<MeshComponent>(e, MeshComponentFactory::CubeMesh(), MeshComponentFactory::CubeIndices(),
						 TextureManager::Get("Ruina/res/textures/texture_palette.png"), model);
	Entity e1 = m.Create();
	m.Add<MeshComponent>(e1, MeshComponentFactory::CubeMesh(), MeshComponentFactory::CubeIndices(),
						 TextureManager::Get("Ruina/res/textures/texture_palette.png"),
						 glm::translate(model, {-3, 0, 0}));

}

void Scene::AddTriangle() {
	Entity e2 = m.Create();
	glm::mat4 model = glm::mat4(1.0f);
	m.Add<MeshComponent>(e2, MeshComponentFactory::TriangleMesh(), MeshComponentFactory::TriangleIndices(),
						 TextureManager::Get("Ruina/res/textures/texture_palette.png"), model);
}

void Scene::ChangePosition(float x, float y, float z) {
	if (selected != -1) {
		auto g = m.CreateGroup<MeshComponent>();
		auto[mesh] = g.Get(selected);
		mesh->model = glm::translate(base_model, glm::vec3(x, y, z));
	}
}
