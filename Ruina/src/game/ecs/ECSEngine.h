#pragma once
#include "ComponentManager.h"
#include "ECS.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "SystemManager.h"

class ECSEngine {
public:
	static EntityManager& entity_manager() { static EntityManager em; return em;};
	static ComponentManager& component_manager() { static ComponentManager cm; return cm;};
	static SystemManager& system_manager() { static SystemManager sm; return sm;};
	static EventManager& event_manager() { static EventManager em; return em;};
};