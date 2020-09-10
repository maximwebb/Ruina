#pragma once
#include "Entity.h"

class ChunkEntity : public Entity {
public:
	ChunkEntity(EntityId id) : Entity(id) {}
};