#include "Entity.h"
#include <iostream>

Entity::Entity(EntityId id, EntityType type) : m_id(id), m_type(type), m_components() {}

void Entity::AddComponent(ComponentId component_id) {
	m_components.push_back(component_id);
}

std::vector<ComponentId>& Entity::GetComponents() {
	return m_components;
};

Speaker::Speaker(EntityId id, EntityType type) : Entity(id, type) {
	std::cout << "Logged something :DDD" << std::endl;
}
