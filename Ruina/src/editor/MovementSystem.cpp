#include "MovementSystem.h"
#include <utility>

MovementSystem::MovementSystem(Manager& m, std::shared_ptr<Camera> camera, GLFWwindow* window,
							   float move_speed, float look_speed)
: System(m), camera(std::move(camera)), window(window), move_speed(move_speed), look_speed(look_speed) {
	Subscribe<GameTickEvent>(HANDLER(Update));
}

void MovementSystem::Update(const Event& e) {
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