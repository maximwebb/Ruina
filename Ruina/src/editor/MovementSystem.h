#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Event.h"
#include "Manager.h"
#include "System.h"
#include "WindowEventSystem.h"

class MovementSystem : public System {
public:
    MovementSystem(Manager&, std::shared_ptr<Camera>, GLFWwindow*, float move_speed, float look_speed);
    void Update(const Event&);
    std::shared_ptr<Camera> camera;

private:
	float move_speed;
	float look_speed;
	GLFWwindow* window{};
};