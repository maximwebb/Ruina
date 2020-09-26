#pragma once
#include <vector>
#include "ComponentManager.h"
#include "ECS.h"

class Entity {
	friend class ComponentManager;
public:
	Entity(EntityId id);
	std::vector<ComponentId>& GetComponents();

	template<typename T, typename... ARGS>
	void AddComponent(ComponentManager& component_manager, ARGS... args) {
		component_manager.CreateComponent<T>(m_id, args...);
	}
public:
	EntityId m_id;
private:
	std::vector<ComponentId> m_components;
	void AddComponentById(ComponentId component_id);

};

class Speaker : public Entity {
public:
	Speaker(EntityId id);
};

class NotAnEntity {
public:
	NotAnEntity(EntityId id) : m_id(id) {};
	EntityId m_id;
};