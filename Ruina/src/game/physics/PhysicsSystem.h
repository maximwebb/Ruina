#pragma once

#include "ECSEngine.h"
#include "System.h"
#include "MotionComponent.h"

class PhysicsSystem : public System {
public:
	PhysicsSystem(SystemId id);

	void Update(const Event&) override;
};

