#include "Scene.h"

Scene::Scene(GLFWwindow* window) : m(), render_system(m), window(window), e(m.Create()) {
	AddCube();
//	AddTriangle();
	movement_system = std::make_unique<MovementSystem>(m, render_system.camera, window, 0.15f, 0.02f);
	object_selection_system = std::make_unique<ObjectSelectionSystem>(m, render_system.camera, window);
	window_event_system = std::make_unique<WindowEventSystem>(m, window);
}

void Scene::OnUpdate(float deltaTime) {
	m.QueueEvent<GameTickEvent>({});
}

void Scene::OnRender() {
	m.QueueEvent<RenderEvent>({});
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
	m.Add<MeshComponent>(e, MeshComponentFactory::CubeMesh(), MeshComponentFactory::CubeIndices(),
						 TextureManager::Get("Ruina/res/textures/texture_palette.png"), model);
	Entity e1 = m.Create();
	m.Add<MeshComponent>(e1, MeshComponentFactory::CubeMesh(), MeshComponentFactory::CubeIndices(),
						 TextureManager::Get("Ruina/res/textures/texture_palette.png"), glm::translate(model, {-3, 0, 0}));

}

void Scene::AddTriangle() {
	Entity e2 = m.Create();
	glm::mat4 model = glm::mat4(1.0f);
	m.Add<MeshComponent>(e2, MeshComponentFactory::TriangleMesh(), MeshComponentFactory::TriangleIndices(),
						 TextureManager::Get("Ruina/res/textures/texture_palette.png"), model);
}

void Scene::ChangePosition(float delta) {
	auto g = m.CreateGroup<MeshComponent>();
	auto [mesh] = g.Get(e);
	mesh->model = glm::translate(mesh->model, glm::vec3(0, 0, delta));
}
