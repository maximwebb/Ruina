#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Event.h"
#include "Manager.h"
#include "System.h"
#include "MeshComponent.h"

class SelectElementEvent : public Event {
public:
	SelectElementEvent(int id, bool clicked) : id(id), clicked(clicked) { }
	const int id;
	const bool clicked;
};

class ObjectSelectionSystem : public System {
public:
    ObjectSelectionSystem(Manager&, std::shared_ptr<Camera>, GLFWwindow*);
	void OnClick(const Event&);
	void TestIntersection(const Event&);
    std::shared_ptr<Camera> camera;

private:
	GLFWwindow* window{};
	int window_width;
	int window_height;
	int prev_hovered;
	int prev_selected;
	bool active_selected;
	float Sign(glm::vec2 u, glm::vec2 v, glm::vec2 w);
};