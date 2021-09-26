#pragma once

#include <TextureCache.h>
#include <PhysicsSystem.h>
#include <MeshComponentFactory.h>
#include "Test.h"
#include "RenderSystem.h"
#include "../game/physics/MotionEntity.h"

namespace test {
	class TestECSRender : public Test {
	public:
		TestECSRender(GLFWwindow*);
		~TestECSRender();

		void OnUpdate(float deltaTime) override;

		void OnRender() override;

		void OnImGuiRender() override;

	private:
	    GLFWwindow* window;
//		SystemId m_id;
//		SystemId phys_id;
//		MotionEntity* sphere;
//		MotionEntity* sphere2;
//		MotionEntity* block1;
//		ComponentId sphere_id;
//		ComponentId sphere_id2;
		Manager m;
		MeshComponentFactory mesh_factory;
		PhysicsSystem physics_system;
		RenderSystem render_system;
		Entity sphere1;
		Entity sphere2;
		Entity cube;
		int depth;
		int count;
		float angle = 1.570796f;
	};
}
