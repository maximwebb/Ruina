#include "Component.h"

Component::Component(ComponentId id, ComponentType type, EntityId entity_id)
	: m_id(id), m_type(type), m_entity_id(entity_id) {}

Logging::Logging(ComponentId id, ComponentType type, EntityId entity_id, const char* message)
	: Component(id, type, entity_id), m_message(message) {}
