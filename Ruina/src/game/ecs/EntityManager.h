#pragma once
#include <iostream>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include "ECS.h"
#include "Entity.h"

class EntityManager {
public:
	EntityManager() : m_current_id(0), m_entities(), m_free_ids() {}

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

		auto pair = m_entities.insert({id, new T(id)});
		return (T*)&(*(pair.first)->second);
	}

	Entity& GetEntity(EntityId id) {
		auto result = m_entities.find(id);
		if (result == m_entities.end()) {
			throw std::exception("Error: Cannot find entity.");
		}
		return *result->second;
	}

	void DestroyEntity(EntityId id) {
		auto result = m_entities.find(id);
		if (result == m_entities.end()) {
			throw std::exception("Error: Cannot find entity.");
		}
		m_entities.erase(id);
		m_free_ids.push(id);
	}

private:
	EntityId m_current_id;
	std::stack<EntityId> m_free_ids;
	std::unordered_map<EntityId, Entity*> m_entities;
};