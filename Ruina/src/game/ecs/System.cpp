#include "System.h"
#include "ECSEngine.h"


LoggingSystem::LoggingSystem(SystemId id) : System(id) {
	SubscribeToEvent<OnLogRequestEvent>();
}

void LoggingSystem::Update(const Event& e) {
	for (auto c : ECSEngine::component_manager().GetComponentGroup<Logging>()) {
		std::cout << ((Logging*) c)->m_message << std::endl;
	}
}