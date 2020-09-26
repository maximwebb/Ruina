#pragma once
#include "ECSEngine.h"
#include "Entity.h"

class MotionEntity : public Entity {
public:
	explicit MotionEntity(EntityId id) : Entity(id) {};

	void AddTorque(Torque torque) {
		MotionComponent* motion_component = ECSEngine::component_manager().GetComponent<MotionComponent>(m_id);
		motion_component->torques.push_back(torque);
	}

	void AddTorque(glm::vec3 force, glm::vec3 distance) {
		MotionComponent* motion_component = ECSEngine::component_manager().GetComponent<MotionComponent>(m_id);
		Torque torque(force, distance);
		motion_component->torques.push_back(torque);
	}
};