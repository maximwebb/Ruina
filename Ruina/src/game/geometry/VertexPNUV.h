#pragma once
#include <glm/glm.hpp>
#include <iostream>

struct VertexPNUV {
	VertexPNUV() = default;
	VertexPNUV(glm::vec3 pos, glm::vec3 norm, glm::vec2 uv) {
		x = pos.x;
		y = pos.y;
		z = pos.z;

		n_x = norm.x;
		n_y = norm.y;
		n_z = norm.z;

		u = uv[0];
		v = uv[1];
	}
	VertexPNUV(float x, float y, float z, float n1, float n2, float n3, float u, float v)
		: x(x), y(y), z(z), n_x(n1), n_y(n2), n_z(n3), u(u), v(v) {}
	float x, y, z;
	float n_x, n_y, n_z;

	float u, v;

	friend std::ostream& operator<<(std::ostream& stream, const VertexPNUV& vertex) {
		stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
		return stream;
	}
};