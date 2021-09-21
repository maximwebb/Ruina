#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Event.h"
#include "Manager.h"
#include "System.h"
#include "MeshComponent.h"

class HoverEvent : public Event {
public:
	HoverEvent(glm::vec2 pos) : pos(pos) {	}
	glm::vec2 pos;
};

class SelectElementEvent : public Event {
public:
	SelectElementEvent(int id) : id(id) { }
	int id;
};

class ObjectSelectionSystem : public System {
public:
    ObjectSelectionSystem(Manager&, std::shared_ptr<Camera>, GLFWwindow*);
    void OnHover(const Event&);
	void OnClick(const Event&);
	void TestIntersection(const Event&);
    std::shared_ptr<Camera> camera;

private:
	GLFWwindow* window{};
	glm::vec<2, double> prev_cursor;
	int prev_hovered;
	float Sign(glm::vec2 u, glm::vec2 v, glm::vec2 w);
};