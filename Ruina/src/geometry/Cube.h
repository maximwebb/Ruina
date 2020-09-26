#pragma once

#include <glm/glm.hpp>
#include "ECS.h"
#include "VertexPNUV.h"

class Cube {
public:
	Cube(glm::ivec3);
	Cube() = default;
	~Cube() = default;
	void GenerateVertexData();
	void GenerateIndexOffset(int offset);
public:
	VertexPNUV m_vertices[24];
	float vertex_data[24 * 8];
	static const int vertex_data_size = 24 * 8 * sizeof(float);
	unsigned int m_indices[36];

	glm::ivec3 chunk_position;

	constexpr static const float m_coordinates[72] = {0.0f, 0.0f, 0.0f,
													  1.0f, 0.0f, 0.0f,
													  0.0f, 1.0f, 0.0f,
													  1.0f, 1.0f, 0.0f,
													  1.0f, 0.0f, 0.0f,
													  1.0f, 0.0f, 1.0f,
													  1.0f, 1.0f, 0.0f,
													  1.0f, 1.0f, 1.0f,
													  1.0f, 0.0f, 1.0f,
													  0.0f, 0.0f, 1.0f,
													  1.0f, 1.0f, 1.0f,
													  0.0f, 1.0f, 1.0f,
													  0.0f, 0.0f, 1.0f,
													  0.0f, 0.0f, 0.0f,
													  0.0f, 1.0f, 1.0f,
													  0.0f, 1.0f, 0.0f,
													  0.0f, 0.0f, 1.0f,
													  1.0f, 0.0f, 1.0f,
													  0.0f, 0.0f, 0.0f,
													  1.0f, 0.0f, 0.0f,
													  0.0f, 1.0f, 0.0f,
													  1.0f, 1.0f, 0.0f,
													  0.0f, 1.0f, 1.0f,
													  1.0f, 1.0f, 1.0f};

	constexpr static const float m_normals[72] = {0.0f, 0.0f, 1.0f,
												  0.0f, 0.0f, 1.0f,
												  0.0f, 0.0f, 1.0f,
												  0.0f, 0.0f, 1.0f,
												  1.0f, 0.0f, 0.0f,
												  1.0f, 0.0f, 0.0f,
												  1.0f, 0.0f, 0.0f,
												  1.0f, 0.0f, 0.0f,
												  0.0f, 0.0f, 1.0f,
												  0.0f, 0.0f, 1.0f,
												  0.0f, 0.0f, 1.0f,
												  0.0f, 0.0f, 1.0f,
											     -1.0f, 0.0f, 0.0f,
											     -1.0f, 0.0f, 0.0f,
											     -1.0f, 0.0f, 0.0f,
											     -1.0f, 0.0f, 0.0f,
												  0.0f, -1.0f, 0.0f,
												  0.0f, -1.0f, 0.0f,
												  0.0f, -1.0f, 0.0f,
												  0.0f, -1.0f, 0.0f,
												  0.0f, 1.0f, 0.0f,
												  0.0f, 1.0f, 0.0f,
												  0.0f, 1.0f, 0.0f,
												  0.0f, 1.0f, 0.0f};
};