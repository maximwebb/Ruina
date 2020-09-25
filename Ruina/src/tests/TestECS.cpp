#include "TestECS.h"
#include "ECSEngine.h"

namespace test {
	TestECS::TestECS() {

		ECSEngine::system_manager().CreateSystem<LoggingSystem>();
		Entity* e1 = ECSEngine::entity_manager().CreateEntity<Speaker>();
		Entity* e2 = ECSEngine::entity_manager().CreateEntity<Speaker>();
		ECSEngine::component_manager().CreateComponent<Logging>(e1->m_id, "This is the first piece of text.");
		ECSEngine::component_manager().CreateComponent<Logging>(e2->m_id, "This is the second piece of text.");

		ECSEngine::event_manager().QueueEvent<OnLogRequestEvent>();
		ECSEngine::event_manager().QueueEvent<OnLogRequestEvent>();

		ECSEngine::event_manager().NotifyListeners();
	}
}