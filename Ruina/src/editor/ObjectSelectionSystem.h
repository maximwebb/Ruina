#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Event.h"
#include "Manager.h"
#include "MeshComponent.h"
#include "System.h"

class SelectElementEvent : public Event {
public:
	SelectElementEvent(int id, bool select) : id(id), select(select) { }
	const int id;
	const bool select;
};

class HoverElementEvent : public Event {
public:
	HoverElementEvent(int id) : id(id) { }
	const int id;
};

class ObjectSelectionSystem : public System {
public:
    ObjectSelectionSystem(Manager&, std::shared_ptr<Camera>, GLFWwindow*);
	void OnClick(const Event&);
	void TestIntersection(const Event&);
    std::shared_ptr<Camera> camera;
	int selected;

private:
	int window_width;
	int window_height;
	int prev_hovered;
	bool active_selected;
	float Sign(glm::vec2 u, glm::vec2 v, glm::vec2 w);
	void Update(const Event& ev);
};