#pragma once
#include <unordered_map>
#include "ECS.h"

class System;

class SystemManager {
public:
	SystemManager();
	template<typename T>
	SystemId CreateSystem() {
		System* system = static_cast<System*>(new T(++m_current_id));
		m_systems.insert({m_current_id, system});
		return m_current_id;
	};
	System* GetSystem(SystemId);
private:
	SystemId m_current_id;
	std::unordered_map<SystemId, System*> m_systems;
};