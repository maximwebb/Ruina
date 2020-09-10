#include "ComponentManager.h"

ComponentManager::ComponentManager() : m_components(), m_grouped_components(), m_current_id(0), m_free_ids() {
//	for (int i = 0; i != (int)ComponentType::END; i++) {
//		m_grouped_components[(ComponentType)i] = std::vector<Component*>();
//	}
}

Component* ComponentManager::GetComponent(ComponentId id) {
	auto result = m_components.find(id);
	if (result == m_components.end()) {
		throw std::exception("Error: Cannot find component");
	}
	return result->second;
}

void ComponentManager::DestroyComponent(ComponentId id) {
	Component* c = m_components.find(id)->second;
	m_components.erase(id);
	m_free_ids.push(id);
	delete c;
}