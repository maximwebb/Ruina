#pragma once
#include "Entity.h"
#include "ECSTypes.h"
#include <unordered_map>
#include <stack>
#include <iostream>
typedef int EntityId;

class EntityManager {
public:
	EntityManager();

	EntityId CreateEntity(EntityType entity_type);
	Entity* GetEntity(EntityId id);
	void DestroyEntity(EntityId id);
private:
	EntityId m_current_id;
	std::stack<EntityId> m_free_ids;
	std::unordered_map<EntityId, Entity*> m_entities;
};