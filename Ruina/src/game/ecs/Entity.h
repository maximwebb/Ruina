#pragma once

#include <vector>
#include "ECSTypes.h"

class Entity {
	friend class ComponentManager;
public:
	Entity(EntityId id, EntityType type);
	std::vector<ComponentId>& GetComponents();

public:
	EntityId m_id;
	EntityType m_type;
private:
	std::vector<ComponentId> m_components;
	void AddComponent(ComponentId component_id);

};

class Speaker : public Entity {
public:
	Speaker(EntityId id, EntityType type);
};