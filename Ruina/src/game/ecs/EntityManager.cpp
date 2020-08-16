#include "EntityManager.h"

EntityManager::EntityManager()
	: m_current_id(0), m_entities(), m_free_ids() {}

EntityId EntityManager::CreateEntity(EntityType entity_type) {
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

Entity *EntityManager::GetEntity(EntityId id) {
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
	delete result->second;
	m_entities.erase(id);
	m_free_ids.push(id);
}

