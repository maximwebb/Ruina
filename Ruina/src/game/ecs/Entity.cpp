#include "Entity.h"

Entity::Entity(EntityId id) : m_id(id), m_components() {}

void Entity::AddComponentById(ComponentId component_id) {
	m_components.push_back(component_id);
}

std::vector<ComponentId>& Entity::GetComponents() {
	return m_components;
};

Speaker::Speaker(EntityId id) : Entity(id) { };