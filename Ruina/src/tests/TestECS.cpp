#include "TestECS.h"

namespace test {
	TestECS::TestECS() : m_entity_manager(EntityManager()) {
		EntityId entity_id = m_entity_manager.CreateEntity(EntityType::Speaker);
		m_component_manager.CreateComponent(ComponentType::Logging, entity_id, "Hello World");

		Entity* e = m_entity_manager.GetEntity(entity_id);

	}
}