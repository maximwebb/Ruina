#pragma once
#include "ECSTypes.h"
#include "Entity.h"
#include <unordered_map>
#include <stack>
#include <iostream>


class EntityManager {
public:
	EntityManager();


	EntityId CreateEntity(EntityType entity_type) {
		EntityId id;
		Entity* e = nullptr;

		if (m_free_ids.empty()) {
			id = ++m_current_id;
		}
		else {
			id = m_free_ids.top();
			m_free_ids.pop();
		}

		/* Translate enum value into Entity type */
		if (entity_type == EntityType::Speaker) {
			e = new Speaker(id, entity_type);
		}

		if (e != nullptr) {
			m_entities.insert({id, e});
		}
		return id;
	}
	Entity* GetEntity(EntityId id);
	void DestroyEntity(EntityId id);


private:
	EntityId m_current_id;
	std::stack<EntityId> m_free_ids;
	std::unordered_map<EntityId, Entity*> m_entities;
};