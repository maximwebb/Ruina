#include "MovementSystem.h"
#include <utility>

MovementSystem::MovementSystem(Manager& m, std::shared_ptr<Camera> camera, GLFWwindow* window,
							   float move_speed, float look_speed)
: System(m), camera(std::move(camera)), window(window), move_speed(move_speed), look_speed(look_speed) {
	Subscribe<GameTickEvent>(HANDLER(Update));
}

void MovementSystem::Update(const Event& ev) {
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
}