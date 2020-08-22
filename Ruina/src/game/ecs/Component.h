#pragma once
#include "ECSTypes.h"

struct Component {
	Component(ComponentId id, ComponentType type, EntityId entity_id)
			: m_id(id), m_type(type), m_entity_id(entity_id) {}
	virtual ComponentId GetComponentId() = 0;
	ComponentId m_id;
	ComponentType m_type;
	EntityId m_entity_id;
};

struct Logging : public Component {
	Logging(ComponentId id, ComponentType type, EntityId entity_id, const char* message)
			: Component(id, type, entity_id), m_message(message), m_logging(false) {}
	ComponentId GetComponentId() override { return m_id; }
	const char* m_message;
	bool m_logging;
};