#pragma once

#include <TextureCache.h>
#include "Test.h"
#include "ECSEngine.h"
#include "RenderSystem.h"
#include "../geometry/Block.h"
#include "../game/physics/MotionEntity.h"

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
		SystemId phys_id;
		MotionEntity* sphere;
		MotionEntity* block1;
		ComponentId sphere_id;
		int depth;
		int count;
		float angle = 1.570796f;
	};
}

