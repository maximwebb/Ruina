#include "EntityManager.h"

EntityManager::EntityManager()
	: m_current_id(0), m_entities(), m_free_ids() {}


Entity& EntityManager::GetEntity(EntityId id) {
	auto result = m_entities.find(id);
	if (result == m_entities.end()) {
		throw std::exception("Error: Cannot find entity.");
	}
	return result->second;
}


void EntityManager::DestroyEntity(EntityId id) {
	auto result = m_entities.find(id);
	if (result == m_entities.end()) {
		throw std::exception("Error: Cannot find entity.");
	}
	// TODO: Perform necessary cleanup for the entity
	m_entities.erase(id);
	m_free_ids.push(id);
}

