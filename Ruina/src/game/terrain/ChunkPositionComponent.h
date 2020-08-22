#pragma once
#include "Component.h"
#include <glm/glm.hpp>

struct ChunkPositionComponent : public Component {
	ChunkPositionComponent(ComponentId id, ComponentType type, EntityId entityId, glm::vec3 pos, EntityId chunk_id)
		: Component(id, type, entityId), chunk_position(pos), chunk_id(chunk_id) {};

	glm::vec3 chunk_position{};
	EntityId chunk_id{};
};