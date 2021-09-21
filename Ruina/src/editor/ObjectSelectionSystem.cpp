#include "ObjectSelectionSystem.h"

ObjectSelectionSystem::ObjectSelectionSystem(Manager& m, std::shared_ptr<Camera> camera, GLFWwindow* window)
: System(m), camera(std::move(camera)), window(window), prev_cursor({0.0, 0.0f}), prev_hovered(-1) {
	Subscribe<GameTickEvent>(HANDLER(OnHover));
	Subscribe<GameTickEvent>(HANDLER(OnClick));
	Subscribe<HoverEvent>(HANDLER(TestIntersection));
}

void ObjectSelectionSystem::OnHover(const Event&) {
	glm::vec<2, double> new_cursor(0.0f);
	glfwGetCursorPos(window, &(new_cursor.x), &(new_cursor.y));
	if (glm::distance(new_cursor, prev_cursor) > 0.0) {
		prev_cursor = new_cursor;
		int* width = new int;
		int* height = new int;
		glfwGetWindowSize(window, width, height);
		double x = 2 * new_cursor.x/(double)(*width) - 1.0;
		double y = 1.0- 2 * new_cursor.y/(double)(*height);
		glm::vec2 pos(x, y);
		m.QueueEvent<HoverEvent>(pos);
	}
}

void ObjectSelectionSystem::TestIntersection(const Event& e) {
	auto* hover_event = (HoverEvent*)&e;
	glm::vec3 pos(hover_event->pos.x, hover_event->pos.y, 1.0f);
	glm::vec3 origin(0.0f);
	auto g = m.CreateGroup<MeshComponent>();
	int selected = -1;
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
		m.QueueEvent<SelectElementEvent>(prev_hovered);
	}
}


float ObjectSelectionSystem::Sign(glm::vec2 u, glm::vec2 v, glm::vec2 w) {
	return (u.x - w.x) * (v.y - w.y) - (v.x - w.x) * (u.y - w.y);
}

// TODO: Event handler to fix GLFW_RELEASE being continually triggered.
void ObjectSelectionSystem::OnClick(const Event&) {

}
