#pragma once

#include "RenderSystem.h"
#include "MeshComponentFactory.h"
#include "Manager.h"
#include "MovementSystem.h"

class Scene {
public:
	Scene(GLFWwindow*);

	void OnUpdate(float deltaTime);
	void OnRender();
	void AddCube();
	void ChangePosition(float delta);

private:
	Manager m;
	RenderSystem render_system;
	std::unique_ptr<MovementSystem> movement_system;
	GLFWwindow* window;
	Entity e;
};