#pragma once
#include "ECS.h"

class Block : public Entity {
public:
	Block(EntityId id, EntityType type) : Entity(id, type) {}
};