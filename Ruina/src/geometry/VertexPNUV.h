#pragma once

#include <glm/glm.hpp>

struct VertexPNUV {
	VertexPNUV() = default;
	VertexPNUV(float x, float y, float z, float n1, float n2, float n3, float u, float v) {
		position = glm::vec3(x, y, z);
		normal = glm::vec3(n1, n2, n3);
		tex_coords = glm::vec2(u, v);
	}
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
};