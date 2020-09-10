#include "System.h"
#include "ECSEngine.h"

void System::SubscribeToEvent(EventType e) {
	ECSEngine::event_manager().RegisterListener(m_id, e);
}


LoggingSystem::LoggingSystem(SystemId id) : System(id) {
	SubscribeToEvent(EventType::OnLogRequest);
}

void LoggingSystem::Update(const Event& e) {
	for (auto c : ECSEngine::component_manager().GetComponentGroup<Logging>())
		//std::cout << dynamic_cast<Logging*>(c)->m_message << std::endl;
		std::cout << ((Logging*) c)->m_message << std::endl;
}