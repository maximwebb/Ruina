#include "SystemManager.h"
#include "ECS.h"

SystemManager::SystemManager() : m_current_id(0) {};

//SystemId SystemManager::CreateSystem(System* system) {
//
//};

System& SystemManager::GetSystem(SystemId id)  {
	auto system = m_systems.find(id);
	if (system == m_systems.end()) {
		throw std::exception("Error: could not find system.");
	}
	return *system->second;
};