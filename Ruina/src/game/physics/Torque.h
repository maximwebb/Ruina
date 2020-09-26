#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

struct Torque {
	Torque(glm::vec3 force, glm::vec3 distance) : force(force), distance(distance) {};
	Torque(glm::vec3 force, glm::vec3 base, glm::vec3 pivot) : force(force), distance() {
		distance = (glm::dot(force, (pivot - base))/glm::dot(force, force)) * force;
	}
	glm::vec3 force;
	glm::vec3 distance;
};
