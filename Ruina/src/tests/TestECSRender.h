#pragma once

#include <TextureCache.h>
#include "Test.h"
#include "ECSEngine.h"
#include "RenderSystem.h"
#include "../game/terrain/Block.h"

namespace test {
	class TestECSRender : public Test {
	public:
		TestECSRender();
		~TestECSRender();

		void OnUpdate(float deltaTime) override;

		void OnRender() override;

		void OnImGuiRender() override;

	private:
		SystemId m_id;
		EntityId sphere;
		ComponentId sphere_id;
		int depth;
		int count;
		float angle = 1.570796f;
	};
}

