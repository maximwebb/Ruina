#pragma once
#include "ECSTypes.h"

class Component {
public:
	Component(ComponentId, ComponentType, EntityId);

public:
	ComponentId m_id;
	ComponentType m_type;
	EntityId m_entity_id;
};

class Logging : public Component {
public:
	Logging(ComponentId, ComponentType, EntityId id, const char* str);
public:
	const char* m_message;
};