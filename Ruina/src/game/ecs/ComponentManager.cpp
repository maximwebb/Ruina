#include "ComponentManager.h"

ComponentManager::ComponentManager() : m_components(), m_grouped_components(), m_current_id(0), m_free_ids() {
	for (int i = 0; i != (int)ComponentType::END; i++) {
		m_grouped_components[(ComponentType)i] = std::vector<Component*>();
	}
}

Component* ComponentManager::GetComponent(ComponentId id) {
	auto result = m_components.find(id);
	if (result == m_components.end()) {
		throw std::exception("Error: Cannot find component");
	}
	return result->second;
}

Component* ComponentManager::GetComponent(ComponentType type, EntityId id) {
	auto components = GetComponentGroup(type);
	auto result = std::find_if(components.begin(), components.end(), [id](Component* x){return x->m_entity_id == id;});
	if (result == components.end()) {
		throw std::exception("Error: Cannot find component type");
	}
}

std::vector<Component*> ComponentManager::GetComponentGroup(ComponentType type) {
	auto result = m_grouped_components.find(type);
	if (result == m_grouped_components.end()) {
		throw std::exception("Error: Cannot find component type");
	}
	return result->second;
}


void ComponentManager::DestroyComponent(ComponentId id) {
	Component* c = m_components.find(id)->second;
	m_components.erase(id);
	m_free_ids.push(id);
	delete c;
}