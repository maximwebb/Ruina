#include "ComponentManager.h"

ComponentManager::ComponentManager() : m_components(), m_grouped_components(), m_current_id(0), m_free_ids() {}

Component* ComponentManager::GetComponent(ComponentId id) {
	auto result = m_components.find(id);
	if (result == m_components.end()) {
		throw std::exception("Error: Cannot find component");
	}
	return result->second;
}

void ComponentManager::DestroyComponent(ComponentId id) {
	Component* c = m_components.find(id)->second;
	std::unordered_set<Component*>& group1 = m_grouped_components.at(typeid(MeshComponent));
	group1.erase(c);
	m_components.erase(id);
	auto group = GetComponentGroup<MeshComponent>();
	m_free_ids.push(id);
	delete c;
}