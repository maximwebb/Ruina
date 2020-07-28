#include "Cube.h"

Cube::Cube() : m_indices{
	0, 2, 1,
	1, 2, 3,

	4, 6, 5,
	5, 6, 7,

	8, 10, 9,
	9, 10, 11,

	12, 14, 13,
	13, 14, 15,

	16, 18, 17,
	17, 18, 19,

	20, 22, 21,
	21, 22, 23
}, vertex_data_size(240 * sizeof(float)) {
	/* Front */
	m_vertices[0] =  Vertex{0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f};
	m_vertices[1] =  Vertex{1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f};
	m_vertices[2] =  Vertex{0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f};
	m_vertices[3] =  Vertex{1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f};

	/* Right */
	m_vertices[4] =  Vertex{1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
	m_vertices[5] =  Vertex{1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	m_vertices[6] =  Vertex{1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	m_vertices[7] =  Vertex{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};

	/* Back */
	m_vertices[8] =  Vertex{1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
	m_vertices[9] =  Vertex{0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	m_vertices[10] = Vertex{1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	m_vertices[11] = Vertex{0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};

	/* Left */
	m_vertices[12] = Vertex{0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
	m_vertices[13] = Vertex{0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	m_vertices[14] = Vertex{0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	m_vertices[15] = Vertex{0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};

	/* Down */
	m_vertices[16] = Vertex{0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
	m_vertices[17] = Vertex{1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	m_vertices[18] = Vertex{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	m_vertices[19] = Vertex{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

	/* Up */
	m_vertices[20] = Vertex{0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
	m_vertices[21] = Vertex{1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	m_vertices[22] = Vertex{0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	m_vertices[23] = Vertex{1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

	for (int i = 0; i < 24; i++) {
		vertex_data[i * 10 + 0] = m_vertices[i].x;
		vertex_data[i * 10 + 1] = m_vertices[i].y;
		vertex_data[i * 10 + 2] = m_vertices[i].z;

		vertex_data[i * 10 + 3] = m_vertices[i].r;
		vertex_data[i * 10 + 4] = m_vertices[i].g;
		vertex_data[i * 10 + 5] = m_vertices[i].b;
		vertex_data[i * 10 + 6] = m_vertices[i].a;

		vertex_data[i * 10 + 7] = m_vertices[i].u;
		vertex_data[i * 10 + 8] = m_vertices[i].v;

		vertex_data[i * 10 + 9] = m_vertices[i].index;
	}
}
