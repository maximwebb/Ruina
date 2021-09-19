#include "Scene.h"

Scene::Scene(GLFWwindow* window) : m(), render_system(m), window(window), e(m.Create()) {
	AddCube();
	movement_system = std::make_unique<MovementSystem>(m, render_system.camera, window, 0.15f, 0.02f);
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

	glm::mat4 model = glm::mat4(0.1);
	m.Add<MeshComponent>(e, MeshComponentFactory::CubeMesh(), MeshComponentFactory::CubeIndices(),
						 TextureManager::Get("Ruina/res/textures/texture_palette.png"), model);
}

void Scene::ChangePosition(float delta) {
	auto g = m.CreateGroup<MeshComponent>();
	auto [mesh] = g.Get(e);
	mesh->model = glm::translate(mesh->model, glm::vec3(0, 0, delta));
}
