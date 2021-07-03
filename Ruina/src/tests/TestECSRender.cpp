#include "TestECSRender.h"
#include "../geometry/MeshComponentFactory.h"

#ifdef WIN32
#include <Windows.h>
#endif


namespace test {
	TestECSRender::TestECSRender(GLFWwindow* window) : window(window), m({}), physics_system(m), render_system(m),
													   sphere1(m.Create()), sphere2(m.Create()) {

		MeshComponentFactory mesh_factory(m);
		depth = 15;
		glm::mat4 model1 = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(10.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(-5.0f, -0.5f, 0.0f));

		glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(-3.0f, -0.5f, 0.0f));
		glm::mat4 model2 = glm::translate(glm::mat4(1), glm::vec3(3.0f, -0.5f, 0.0f));

		mesh_factory.CreateSphereMesh(sphere1, model1, depth);
		mesh_factory.CreateSphereMesh(sphere2, model2, depth);


		glm::vec3 center1 = glm::vec3(-5.0f, -0.5f, 0.0f);
		glm::vec3 center2 = glm::vec3(5.0f, -0.5f, 0.0f);
		glm::vec3 velocity1(0);
		glm::vec3 velocity2(0);

		float mass1 = 5000.0f;
		float mass2 = 1000.0f;

		m.Add<MotionComponent>(sphere1, center1, velocity1, mass1 * 10);
		m.Add<MotionComponent>(sphere2, center2, velocity2, mass2 * 10);
		m.Add<MassComponent>(sphere1, mass1);
		m.Add<MassComponent>(sphere2, mass2);
	}

	TestECSRender::~TestECSRender() {

	}

	void TestECSRender::OnUpdate(float deltaTime) {
		m.QueueEvent<GameTickEvent>({});
	}

	void TestECSRender::OnRender() {
		Test::OnRender();
		m.QueueEvent<RenderEvent>({});
	}

	void TestECSRender::OnImGuiRender() {
		auto camera = render_system.camera;
		float move_speed = 0.15f;
		float look_speed = 0.02f;
#ifdef WIN32
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
#else
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->IncrementPosition(0.0f, 0.0f, move_speed);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->IncrementPosition(move_speed, 0.0f, 0.0f);

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->IncrementPosition(0.0f, 0.0f, -move_speed);

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->IncrementPosition(-move_speed, 0.0f, 0.0f);

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera->IncrementPosition(0.0f, move_speed, 0.0f);

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera->IncrementPosition(0.0f, -move_speed, 0.0f);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camera->IncrementPitch(look_speed);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			camera->IncrementYaw(-look_speed);

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camera->IncrementPitch(-look_speed);

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			camera->IncrementYaw(look_speed);
#endif
	}

}

