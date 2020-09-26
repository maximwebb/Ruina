#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include "Component.h"
#include "Torque.h"

struct MotionComponent : public Component {
	MotionComponent(ComponentId id, EntityId entityId, glm::vec3 center, glm::vec3 velocity)
		: Component(id, entityId), center(center), velocity(velocity), angular_velocity(0, 0.001f, 0.0f), torques() {}

	glm::vec3 center;
	glm::vec3 velocity;
	glm::vec3 angular_velocity;
	std::vector<Torque> torques;
};