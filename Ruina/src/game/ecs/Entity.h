#pragma once
#include "ECSTypes.h"

class Entity {
public:
	Entity(EntityId id, EntityType type);

public:
	EntityId m_id;
	EntityType m_type;
};

class Speaker : public Entity {
public:
	Speaker(EntityId id, EntityType type);
};