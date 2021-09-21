#include "ObjectSelectionSystem.h"
#include <WindowEventSystem.h>

ObjectSelectionSystem::ObjectSelectionSystem(Manager& m, std::shared_ptr<Camera> camera, GLFWwindow* window)
		: System(m), camera(std::move(camera)), window(window), prev_hovered(-1),
		prev_selected(-1), active_selected(false) {
	Subscribe<MouseClickEvent>(HANDLER(OnClick));
	Subscribe<MouseMoveEvent>(HANDLER(TestIntersection));
	glfwGetWindowSize(window, &window_width, &window_height);
}


void ObjectSelectionSystem::TestIntersection(const Event& e) {
	auto mouse_move_event = *(MouseMoveEvent*)&e;
	double x = 2 * mouse_move_event.x/(double)window_width - 1.0;
	double y = 1.0- 2 * mouse_move_event.y/(double)window_height;
	glm::vec3 pos(x, y, 1.0f);
	glm::vec3 origin(0.0f);
	int selected = -1;
	auto g = m.CreateGroup<MeshComponent>();

	/* Test intersection of cursor position with each triangle */
	for (auto id : g) {
		auto [mesh] = g.Get(id);
		auto model = mesh->model;
		auto indices = mesh->indices;
		auto vertices = mesh->vertices;
		for (int i = 0; i < mesh->indices.size(); i += 3) {
			std::vector<glm::vec3> points;
			for (int j = 0; j < 3; j++) {
				glm::vec4 k(vertices.at(8 * indices.at(i + j)),
							vertices.at(8 * indices.at(i + j) + 1),
							vertices.at(8 * indices.at(i + j) + 2), 1.0f);
				glm::vec3 l = camera->view_matrix * model * k;
				l = camera->proj_matrix * glm::vec4(l, 0.0f);
				points.emplace_back(glm::vec3(l));
			}
			glm::vec2 a = glm::vec2(points.at(0).x/points.at(0).z, points.at(0).y/points.at(0).z);
			glm::vec2 b = glm::vec2(points.at(1).x/points.at(1).z, points.at(1).y/points.at(1).z);
			glm::vec2 c = glm::vec2(points.at(2).x/points.at(2).z, points.at(2).y/points.at(2).z);
			float d1 = Sign(pos, a, b);
			float d2 = Sign(pos, b, c);
			float d3 = Sign(pos, c, a);
			if (!(((d1 < 0) || (d2 < 0) || (d3 < 0))
			&& ((d1 > 0) || (d2 > 0) || (d3 > 0)))) {
				selected = id;
			}
		}
	}
	if (selected != prev_hovered) {
		prev_hovered = selected;
		if (!active_selected) {
			m.QueueEvent<SelectElementEvent>({prev_hovered, false});
		}
	}
}


float ObjectSelectionSystem::Sign(glm::vec2 u, glm::vec2 v, glm::vec2 w) {
	return (u.x - w.x) * (v.y - w.y) - (v.x - w.x) * (u.y - w.y);
}


void ObjectSelectionSystem::OnClick(const Event& ev) {
	MouseClickEvent e = *(MouseClickEvent*)(&ev);
	if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
		if (prev_hovered == prev_selected) {
			prev_selected = -1;
		} else {
			prev_selected = prev_hovered;
		}
		active_selected = (prev_selected != -1);
		m.QueueEvent<SelectElementEvent>({prev_selected, true});
	}
}
