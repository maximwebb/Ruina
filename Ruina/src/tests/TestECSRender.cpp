#include <Windows.h>
#include "TestECSRender.h"
#include "../geometry/MeshComponentFactory.h"

namespace test {
	TestECSRender::TestECSRender() {
		m_id = ECSEngine::system_manager().CreateSystem<RenderSystem>();
		EntityId block1 = ECSEngine::entity_manager().CreateEntity<Block>();
		EntityId block2 = ECSEngine::entity_manager().CreateEntity<Block>();
		EntityId block3 = ECSEngine::entity_manager().CreateEntity<Block>();
		EntityId block4 = ECSEngine::entity_manager().CreateEntity<Block>();
		glm::mat4 model1 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(1.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(-0.5f, -0.5f, 0.0f));

		glm::mat4 model2 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(1.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(-2.0f, -0.5f, 0.0f));

		glm::mat4 model3 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(1.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(-3.5f, -0.5f, 0.0f));

		glm::mat4 model4 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(1.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(-5.0f, -0.5f, 0.0f));

		MeshComponentFactory::CreateCubeMesh(block1, model1);
		MeshComponentFactory::CreateCubeMesh(block2, model2);
		MeshComponentFactory::CreateCubeMesh(block3, model3);
		MeshComponentFactory::CreateCubeMesh(block4, model4);
	}

	TestECSRender::~TestECSRender() {

	}

	void TestECSRender::OnUpdate(float deltaTime) {
		Test::OnUpdate(deltaTime);
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

