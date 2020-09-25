#include <Windows.h>
#include "TestECSRender.h"
#include "../geometry/MeshComponentFactory.h"

namespace test {
	TestECSRender::TestECSRender() {
		m_id = ECSEngine::system_manager().CreateSystem<RenderSystem>();
		EntityId block1 = ECSEngine::entity_manager().CreateEntity<Block>();
		sphere = ECSEngine::entity_manager().CreateEntity<Block>();

		depth = 15;

		glm::mat4 model1 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(1.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(-5.0f, -0.5f, 0.0f));

		glm::mat4 model = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
		sphere_id = MeshComponentFactory::CreateSphereMesh(sphere, model, depth);
		MeshComponentFactory::CreateCubeMesh(block1, model1);
	}

	TestECSRender::~TestECSRender() {

	}

	void TestECSRender::OnUpdate(float deltaTime) {
		dynamic_cast<RenderSystem*>(ECSEngine::system_manager().GetSystem(m_id))->RemoveMeshComponent(sphere_id);
		sphere = ECSEngine::entity_manager().CreateEntity<Block>();
		angle += 0.05f;
		glm::mat4 model = glm::rotate(
							glm::scale(glm::mat4(1), glm::vec3(3)),
						angle, glm::vec3(0, 1, 0));
		sphere_id = MeshComponentFactory::CreateSphereMesh(sphere, model, depth);
	}

	void TestECSRender::OnRender() {
		Test::OnRender();
		ECSEngine::event_manager().QueueEvent<OnRenderEvent>();
		ECSEngine::event_manager().NotifyListeners();
	}

	void TestECSRender::OnImGuiRender() {
		std::shared_ptr<Camera> camera = dynamic_cast<RenderSystem*>(ECSEngine::system_manager().GetSystem(m_id))->m_camera;
		float move_speed = 0.15f;
		float look_speed = 0.02f;
		Camera c = *camera;
		if (GetKeyState('W') & 0x8000)
			camera->IncrementPosition(0.0f, 0.0f, move_speed);

		if (GetKeyState('A') & 0x8000)
			camera->IncrementPosition(move_speed, 0.0f, 0.0f);

		if (GetKeyState('S') & 0x8000)
			camera->IncrementPosition(0.0f, 0.0f, -move_speed);

		if (GetKeyState('D') & 0x8000)
			camera->IncrementPosition(-move_speed, 0.0f, 0.0f);

		if (GetKeyState(VK_SPACE) & 0x8000)
			camera->IncrementPosition(0.0f, move_speed, 0.0f);

		if (GetKeyState(VK_SHIFT) & 0x8000)
			camera->IncrementPosition(0.0f, -move_speed, 0.0f);

		if (GetKeyState(VK_UP) & 0x8000)
			camera->IncrementPitch(look_speed);

		if (GetKeyState(VK_LEFT) & 0x8000)
			camera->IncrementYaw(-look_speed);

		if (GetKeyState(VK_DOWN) & 0x8000)
			camera->IncrementPitch(-look_speed);

		if (GetKeyState(VK_RIGHT) & 0x8000)
			camera->IncrementYaw(look_speed);
	}
}

