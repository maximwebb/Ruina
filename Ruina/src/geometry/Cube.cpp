#include "Cube.h"

Cube::Cube(glm::ivec3 chunk_position) : m_indices{
	0, 1, 2,
	2, 1, 3,

	4, 5, 6,
	6, 5, 7,

	8, 9, 10,
	10, 9, 11,

	12, 13, 14,
	14, 13, 15,

	16, 17, 18,
	18, 17, 19,

	20, 21, 22,
	22, 21, 23
}, chunk_position(chunk_position) {
	/* Front */
    m_vertices[0] =  Vertex{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.333f, 0.0f, 1.0f};
    m_vertices[1] =  Vertex{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    m_vertices[2] =  Vertex{0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.333f, 0.5f, 1.0f};
    m_vertices[3] =  Vertex{1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f};

	/* Right */
	m_vertices[4] =  Vertex{1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f, 0.0f, 1.0f, 0.667f, 0.0f, 1.0f};
	m_vertices[5] =  Vertex{1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f, 0.0f, 1.0f, 0.333f, 0.0f, 1.0f};
	m_vertices[6] =  Vertex{1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f, 0.0f, 1.0f, 0.667f, 0.5f, 1.0f};
	m_vertices[7] =  Vertex{1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f, 0.0f, 1.0f, 0.333f, 0.5f, 1.0f};

	/* Back */
	m_vertices[8] =  Vertex{1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	m_vertices[9] =  Vertex{0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.0f, 1.0f};
	m_vertices[10] = Vertex{1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f};
	m_vertices[11] = Vertex{0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.5f, 1.0f};

	/* Left */
	m_vertices[12] = Vertex{0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.333f, 0.5f, 1.0f};
	m_vertices[13] = Vertex{0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f};
	m_vertices[14] = Vertex{0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.333f, 1.0f, 1.0f};
	m_vertices[15] = Vertex{0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

	/* Down */
	m_vertices[16] = Vertex{0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.667f, 0.5f, 1.0f};
	m_vertices[17] = Vertex{1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.333f, 0.5f, 1.0f};
	m_vertices[18] = Vertex{0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.667f, 1.0f, 1.0f};
	m_vertices[19] = Vertex{1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.333f, 1.0f, 1.0f};

	/* Up */
	m_vertices[20] = Vertex{0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f};
	m_vertices[21] = Vertex{1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.667f, 0.5f, 1.0f};
	m_vertices[22] = Vertex{0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
	m_vertices[23] = Vertex{1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.667f, 1.0f, 1.0f};

	GenerateVertexData();
}

/* Recalculates all of the raw vertex data */
void Cube::GenerateVertexData() {
	for (int i = 0; i < 24; i++) {
		vertex_data[i * 13 + 0] = m_vertices[i].x + chunk_position.x;
		vertex_data[i * 13 + 1] = m_vertices[i].y + chunk_position.y;
		vertex_data[i * 13 + 2] = m_vertices[i].z + chunk_position.z;

		vertex_data[i * 13 + 3] = m_vertices[i].n_x;
		vertex_data[i * 13 + 4] = m_vertices[i].n_y;
		vertex_data[i * 13 + 5] = m_vertices[i].n_z;

		vertex_data[i * 13 + 6] = m_vertices[i].r;
		vertex_data[i * 13 + 7] = m_vertices[i].g;
		vertex_data[i * 13 + 8] = m_vertices[i].b;
		vertex_data[i * 13 + 9] = m_vertices[i].a;

		vertex_data[i * 13 + 10] = m_vertices[i].u;
		vertex_data[i * 13 + 11] = m_vertices[i].v;

		vertex_data[i * 13 + 12] = m_vertices[i].index;
	}
}

/* Calculates indices with an offset applied */
void Cube::GenerateIndexOffset(int offset) {
	for (int i = 0; i < 36; i++) {
		m_indices[i] += offset;
	}
}
