#include <vector>
#include <ECSEngine.h>
#include "Cube.h"
#include "VertexPNUV.h"
#include "TextureData.h"

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
    m_vertices[0] = VertexPNUV{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.333f, 0.0f};
    m_vertices[1] = VertexPNUV{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    m_vertices[2] = VertexPNUV{0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.333f, 0.5f};
    m_vertices[3] = VertexPNUV{1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f};

	/* Right */
	m_vertices[4] = VertexPNUV{1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.667f, 0.0f};
	m_vertices[5] = VertexPNUV{1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.333f, 0.0f};
	m_vertices[6] = VertexPNUV{1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.667f, 0.5f};
	m_vertices[7] = VertexPNUV{1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.333f, 0.5f};

	/* Back */
	m_vertices[8] = VertexPNUV{1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f};
	m_vertices[9] = VertexPNUV{0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.0f};
	m_vertices[10] = VertexPNUV{1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f};
	m_vertices[11] = VertexPNUV{0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.5f};

	/* Left */
	m_vertices[12] = VertexPNUV{0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.333f, 0.5f};
	m_vertices[13] = VertexPNUV{0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.5f};
	m_vertices[14] = VertexPNUV{0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.333f, 1.0f};
	m_vertices[15] = VertexPNUV{0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	/* Down */
	m_vertices[16] = VertexPNUV{0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.667f, 0.5f};
	m_vertices[17] = VertexPNUV{1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.333f, 0.5f};
	m_vertices[18] = VertexPNUV{0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.667f, 1.0f};
	m_vertices[19] = VertexPNUV{1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.333f, 1.0f};

	/* Up */
	m_vertices[20] = VertexPNUV{0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f};
	m_vertices[21] = VertexPNUV{1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.667f, 0.5f};
	m_vertices[22] = VertexPNUV{0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	m_vertices[23] = VertexPNUV{1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.667f, 1.0f};

	GenerateVertexData();
}

/* Recalculates all of the raw vertex data */
void Cube::GenerateVertexData() {
	for (int i = 0; i < 24; i++) {
		vertex_data[i * 8 + 0] = m_vertices[i].position.x + chunk_position.x;
		vertex_data[i * 8 + 1] = m_vertices[i].position.y + chunk_position.y;
		vertex_data[i * 8 + 2] = m_vertices[i].position.z + chunk_position.z;

		vertex_data[i * 8 + 3] = m_vertices[i].normal.x;
		vertex_data[i * 8 + 4] = m_vertices[i].normal.y;
		vertex_data[i * 8 + 5] = m_vertices[i].normal.z;

		vertex_data[i * 8 + 6] = m_vertices[i].tex_coords[0];
		vertex_data[i * 8 + 7] = m_vertices[i].tex_coords[1];
	}
}

/* Calculates indices with an offset applied */
void Cube::GenerateIndexOffset(int offset) {
	for (int i = 0; i < 36; i++) {
		m_indices[i] += offset;
	}
}

