#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_set>
#include "Event.h"
#include "Manager.h"
#include "MotionComponent.h"
#include "System.h"

class PhysicsSystem : public System {
public:
	explicit PhysicsSystem(Manager& m);
	void Update(const Event&);
	glm::vec3 CalculateGravity(float mass, float mass_other, glm::vec3 center, glm::vec3 center_other);
};