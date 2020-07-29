#pragma once

#include <glm/glm.hpp>
#include "Vertex.h"

class Cube {
public:
	Cube(glm::ivec3);
	Cube() = default;
	~Cube() = default;
	void GenerateVertexData();
	void GenerateIndexOffset(int offset);
public:
	Vertex m_vertices[24];
	float vertex_data[24 * 13];
	static const int vertex_data_size = 24 * 13 * sizeof(float);
	unsigned int m_indices[36];

	glm::ivec3 chunk_position;
};