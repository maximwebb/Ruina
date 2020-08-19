#pragma once
#include "Component.h"
#include "ECSTypes.h"
#include <unordered_map>
#include <stack>

class ComponentManager {
public:
	ComponentManager();

	template<typename... ARGS>
	ComponentId CreateComponent(ComponentType component_type, EntityId entity_id, ARGS... args) {
		ComponentId id;
		Component* c = nullptr;

		if (m_free_ids.empty()) {
			id = ++m_current_id;
		}
		else {
			id = m_free_ids.top();
			m_free_ids.pop();
		}

		/* Translate enum value into Component type */
		if (component_type == ComponentType::Logging) {
			c = new Logging(id, component_type, entity_id, args...);
		}

		if (c != nullptr) {
			m_components.insert({id, c});
			m_grouped_components[component_type].push_back(c);
		}
		return id;
	};

	Component* GetComponent(ComponentId);
	Component* GetComponent(ComponentType, EntityId);

	std::vector<Component*> GetComponentGroup(ComponentType);

	void DestroyComponent(ComponentId);

private:
	std::unordered_map<ComponentId, Component*> m_components;
	std::unordered_map<ComponentType, std::vector<Component*>> m_grouped_components;
	ComponentId m_current_id;
	std::stack<ComponentId> m_free_ids;


};