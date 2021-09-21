#include "WindowEventSystem.h"


WindowEventSystem::WindowEventSystem(Manager& m, GLFWwindow* window) : System(m), window(window),
																	   prev_xpos(0), prev_ypos(0) {
	glfwSetWindowUserPointer(window, static_cast<void*>(this));

	glfwSetMouseButtonCallback(window,
		[](GLFWwindow* window, int button, int action, int mods) {
			auto self = static_cast<WindowEventSystem*>(glfwGetWindowUserPointer(window));
			self->MouseClickCallback(window, button, action, mods);
		}
	);

	glfwSetCursorPosCallback(window,
		[](GLFWwindow* window, double x, double y) {
			auto self = static_cast<WindowEventSystem*>(glfwGetWindowUserPointer(window));
			self->MouseMoveCallback(window, x, y);
		}
	);

	glfwSetKeyCallback(window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods) {
		   auto self = static_cast<WindowEventSystem*>(glfwGetWindowUserPointer(window));
		   self->KeyCallback(window, key, scancode, action, mods);
		}
	);
}


void WindowEventSystem::MouseClickCallback(GLFWwindow* w, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		int button_state = 0;
		if (mouse_button_states.find(button) != mouse_button_states.end()) {
			button_state = mouse_button_states.at(button);
		}
		/* Map stores number of frames button has been held for */
		mouse_button_states.insert_or_assign(button, (button_state == INT32_MAX) ? button_state : button_state + 1);
		if (button_state == 0) {
			m.QueueEvent<MouseClickEvent>(button);
		}
	}

	if (action == GLFW_RELEASE) {
		if (mouse_button_states.find(button) != mouse_button_states.end()) {
			if (mouse_button_states.at(button) != 0) {
				mouse_button_states.insert_or_assign(button, 0);
			}
		}
	}
}


void WindowEventSystem::MouseMoveCallback(GLFWwindow* w, double x, double y) {
	if (x != prev_xpos || y != prev_ypos) {
		m.QueueEvent<MouseMoveEvent>({x, y});
	}
}


void WindowEventSystem::KeyCallback(GLFWwindow* w, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		m.QueueEvent<KeyDownEvent>(key);
		int key_state = 0;
		if (key_states.find(key) != key_states.end()) {
			if ((key_state = key_states.at(key)) == 0) {
				m.QueueEvent<KeyDownEvent>(key);
			}
		}
		/* Map stores number of frames key has been held for */
		key_states.insert_or_assign(key, (key_state == INT32_MAX) ? key_state : key_state + 1);
	}

	if (action == GLFW_RELEASE) {
		if (key_states.find(key) != key_states.end()) {
			if (key_states.at(key) != 0) {
				key_states.insert_or_assign(key, 0);
				m.QueueEvent<KeyUpEvent>(key);
			}
		}
	}
}