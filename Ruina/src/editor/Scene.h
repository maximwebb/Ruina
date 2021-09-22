#pragma once

#include "RenderSystem.h"
#include "MeshComponentFactory.h"
#include "Manager.h"
#include "MovementSystem.h"
#include "ObjectSelectionSystem.h"
#include "WindowEventSystem.h"

class Scene {
public:
	Scene(GLFWwindow*);

	void OnUpdate(float deltaTime);
	void OnRender();
	void OnImGuiRender();
	void UpdateSelected(const Event& ev);
	void AddCube();
	void AddTriangle();
	void ChangePosition(float x, float y, float z);

private:
	Manager m;
	RenderSystem render_system;
	std::unique_ptr<MovementSystem> movement_system;
	std::unique_ptr<ObjectSelectionSystem> object_selection_system;
	std::unique_ptr<WindowEventSystem> window_event_system;
	GLFWwindow* window;
	int selected;
	glm::mat4 base_model;
	glm::vec3 translation;
};