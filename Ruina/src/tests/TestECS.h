#pragma once

#include "Test.h"
#include "ecs/ECS.h"

namespace test {
	class TestECS : public Test {
	public:
		TestECS();

		EntityManager m_entity_manager;
		ComponentManager m_component_manager;
	};

}