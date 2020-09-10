#pragma once
#include "Component.h"
#include "../geometry/Cube.h"
#include <glm/glm.hpp>
#include <vector>

struct ChunkPositionComponent : public Component {
	ChunkPositionComponent(ComponentId id, EntityId entityId, glm::vec3 pos, EntityId chunk_id)
		: Component(id, entityId), chunk_position(pos), chunk_id(chunk_id) {
		std::copy(std::begin(Cube::m_coordinates), std::end(Cube::m_coordinates), std::back_inserter(vertex_positions));
		std::copy(std::begin(Cube::m_normals), std::end(Cube::m_normals), std::back_inserter(vertex_normals));
	};

	glm::vec3 chunk_position{};
	EntityId chunk_id{};
	std::vector<float> vertex_positions;
	std::vector<float> vertex_normals;
};