#include <Windows.h>
#include "TestECSRender.h"
#include "../geometry/MeshComponentFactory.h"
#include "../game/physics/MotionComponent.h"
#include "../game/physics/PhysicsSystem.h"


namespace test {
	TestECSRender::TestECSRender() {
		m_id = ECSEngine::system_manager().CreateSystem<RenderSystem>();
		phys_id = ECSEngine::system_manager().CreateSystem<PhysicsSystem>();
		sphere = ECSEngine::entity_manager().CreateEntity<MotionEntity>();
		block1 = ECSEngine::entity_manager().CreateEntity<MotionEntity>();

		depth = 15;

		glm::mat4 model1 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(3.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(-5.0f, -0.5f, 0.0f));

		glm::mat4 model = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
		sphere_id = MeshComponentFactory::CreateSphereMesh(sphere->m_id, model, depth);
		MeshComponentFactory::CreateCubeMesh(block1->m_id, model1);
		glm::vec3 center = glm::vec3(-5.0f, -0.5f, 0.0f);
		glm::vec3 velocity(0);
		ECSEngine::component_manager().CreateComponent<MotionComponent>(sphere->m_id, center, velocity);
		ECSEngine::component_manager().CreateComponent<MotionComponent>(block1->m_id, center, velocity);
		sphere->AddTorque(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		sphere->AddTorque(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		block1->AddTorque(glm::vec3(0.0f, 0.0f, 0.01f), glm::vec3(-1.0f, 0.0f, 0.0f));
	}

	TestECSRender::~TestECSRender() {

	}

	void TestECSRender::OnUpdate(float deltaTime) {
		ECSEngine::event_manager().QueueEvent<OnGameTickEvent>();
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

