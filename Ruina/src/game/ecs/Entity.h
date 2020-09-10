#pragma once

#include <vector>
#include "ECSTypes.h"
#include "ComponentManager.h"

class Entity {
	friend class ComponentManager;
public:
	Entity(EntityId id, EntityType type);
	std::vector<ComponentId>& GetComponents();

	template<typename T, typename... ARGS>
	void AddComponent(ComponentManager& component_manager, ARGS... args) {
		component_manager.CreateComponent<T>(m_id, args...);
	}
public:
	EntityId m_id;
	EntityType m_type;
private:
	std::vector<ComponentId> m_components;
	void AddComponentById(ComponentId component_id);

};

class Speaker : public Entity {
public:
	Speaker(EntityId id, EntityType type);
};