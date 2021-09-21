#pragma once

#include <GLFW/glfw3.h>
#include "Event.h"
#include "Manager.h"

class MouseClickEvent : public Event {
public:
	MouseClickEvent(int button) : button(button) {};
	int button;
};

class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(double x, double y) : x(x), y(y) {};
	double x, y;
};


class KeyUpEvent : public Event {
public:
	KeyUpEvent(int key) : key(key) {};
	int key;
};


class KeyDownEvent : public Event {
public:
	KeyDownEvent(int key) : key(key) {};
	int key;
};

/* Handles the queuing of window I/O events */
class WindowEventSystem : public System {
public:
	WindowEventSystem(Manager&, GLFWwindow*);
	WindowEventSystem(const WindowEventSystem&) = delete;
	WindowEventSystem& operator=(const WindowEventSystem&) = delete;
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
private:
	GLFWwindow* window;
	std::unordered_map<int, int> mouse_button_states;
	std::unordered_map<int, int> key_states;
	double prev_xpos, prev_ypos;
};
