#pragma once
#include <unordered_map>
#include "ECS.h"

class System;

class SystemManager {
public:
	SystemManager() : m_current_id(0) {};

	template<typename T>
	SystemId CreateSystem() {
		m_systems.insert({m_current_id, new T(++m_current_id)});
		return m_current_id;
	}

	System* GetSystem(SystemId id)  {
		auto system = m_systems.find(id);
		if (system == m_systems.end()) {
			throw std::exception("Error: could not find system.");
		}
		return system->second;
	}

private:
	SystemId m_current_id;
	std::unordered_map<SystemId, System*> m_systems;
};