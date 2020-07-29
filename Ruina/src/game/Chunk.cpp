#include "Chunk.h"
#include <xutility>

Chunk::Chunk(unsigned int size)
	: m_size(size), m_cubes_count(0), m_vertex_data_size(0) {
	m_vertex_data.reserve(m_size * m_size * m_size);
}

Cube& Chunk::GetCube(unsigned int x, unsigned int y, unsigned int z) {
	if (x >= m_size || y >= m_size || z >= m_size) {
		throw &"Error: cube coordinates exceed "[m_size];
	}
	return m_cubes[{x, y, z}];
}

void Chunk::SetCube(unsigned int x, unsigned int y, unsigned int z) {
	if (x >= m_size || y >= m_size || z >= m_size) {
		throw &"Error: cube coordinates exceed " [ m_size];
	}
	m_cubes.insert({{x, y, z}, Cube(glm::ivec3(x, y, z))});
	m_cubes_count = m_cubes.size();
}

/* Generates the data for the vertex and index buffer */
void Chunk::GenerateRenderingData() {
	int index = 0;
	for (auto& it : m_cubes) {
		it.second.GenerateVertexData();
		it.second.GenerateIndexOffset(index);
		m_vertex_data.insert(m_vertex_data.end(), std::begin(it.second.vertex_data), std::end(it.second.vertex_data));
		m_index_data.insert(m_index_data.end(), std::begin(it.second.m_indices), std::end(it.second.m_indices));
		index += 24;
	}
	m_vertex_data_size = m_cubes_count * Cube::vertex_data_size;
	m_index_data_size = m_cubes_count * 36;
};