#include "TestECS.h"

namespace test {
	TestECS::TestECS() {

		ECSEngine::system_manager().CreateSystem<LoggingSystem>();
		EntityId e_id1 = ECSEngine::entity_manager().CreateEntity(EntityType::Speaker);
		EntityId e_id2 = ECSEngine::entity_manager().CreateEntity(EntityType::Speaker);
		ECSEngine::component_manager().CreateComponent(ComponentType::Logging, e_id1, "This is the first piece of text.");
		ECSEngine::component_manager().CreateComponent(ComponentType::Logging, e_id2, "This is the second piece of text.");

		ECSEngine::event_manager().QueueEvent<EventOnLogRequest>();
		ECSEngine::event_manager().QueueEvent<EventOnLogRequest>();

		ECSEngine::event_manager().NotifyListeners();
	}
}