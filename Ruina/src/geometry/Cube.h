#pragma once
#include "Vertex.h"

struct Triangle {
	Vertex vertices[3];
	int indices[3];
};

class Cube {
public:
	Cube();
	Vertex m_vertices[24];
	const unsigned int m_indices[36];
	float vertex_data[24 * 13];
	const int vertex_data_size;
};