#pragma once
#include "ECSTypes.h"

class Component {
public:
	Component(ComponentId, ComponentType, EntityId);
	virtual ComponentId GetComponentId() = 0;
public:
	ComponentId m_id;
	ComponentType m_type;
	EntityId m_entity_id;
};

class Logging : public Component {
public:
	Logging(ComponentId, ComponentType, EntityId id, const char* str);
	ComponentId GetComponentId() override { return m_id; }
public:
	const char* m_message;
	bool m_logging;
};