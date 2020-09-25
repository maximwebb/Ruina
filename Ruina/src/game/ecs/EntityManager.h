#pragma once
#include "ECSTypes.h"
#include "Entity.h"
#include <unordered_map>
#include <stack>
#include <iostream>
#include <type_traits>

class EntityManager {
public:
	EntityManager();

	template<typename T>
	T* CreateEntity() {
		static_assert(std::is_base_of<Entity, T>::value, "Error: invalid entity type");

		EntityId id;
		if (m_free_ids.empty()) {
			id = ++m_current_id;
		}
		else {
			id = m_free_ids.top();
			m_free_ids.pop();
		}

		T* e = new T(id);
		m_entities.insert({id, *e});
		return e;
	}
	Entity& GetEntity(EntityId id);
	void DestroyEntity(EntityId id);


private:
	EntityId m_current_id;
	std::stack<EntityId> m_free_ids;
	std::unordered_map<EntityId, Entity> m_entities;
};