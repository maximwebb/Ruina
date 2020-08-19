#pragma once
#include "ECS.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class ECSEngine {
public:
	static EntityManager& entity_manager() { static EntityManager em; return em;};
	static ComponentManager& component_manager() { static ComponentManager cm; return cm;};
	static SystemManager& system_manager() { static SystemManager sm; return sm;};
	static EventManager& event_manager() { static EventManager em; return em;};
//	static EntityManager& entity_manager;
//	static ComponentManager& component_manager;
//	static SystemManager& system_manager;
//	static EventManager& event_manager;


};

//EntityManager ECSEngine::entity_manager;
//ComponentManager ECSEngine::component_manager;
//SystemManager ECSEngine::system_manager;
//EventManager ECSEngine::event_manager;