#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "ECSEngine.h"
#include "MotionComponent.h"
#include "System.h"

class PhysicsSystem : public System {
public:
	explicit PhysicsSystem(SystemId id);
	void Update(const Event&) override;
};