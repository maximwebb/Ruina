#pragma once
#include "ECS.h"

struct Component {
	Component(ComponentId id, EntityId entity_id)
			: m_id(id), m_entity_id(entity_id) {}
	ComponentId GetComponentId() { return m_id; }
	ComponentId m_id;
	EntityId m_entity_id;
};

struct Logging : public Component {
	Logging(ComponentId id, EntityId entity_id, const char* message)
			: Component(id, entity_id), m_message(message), m_logging(false) {}
	const char* m_message;
	bool m_logging;
};