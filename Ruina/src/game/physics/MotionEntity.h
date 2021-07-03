#pragma once
#include "Manager.h"
#include "Entity.h"
#include "MotionComponent.h"
#include "Torque.h"

class MotionEntity : public Entity {
private:
    Manager& m;
public:
	explicit MotionEntity(Entity id, Manager& m) : Entity(id), m(m) {};

//	void AddTorque(Torque torque) {
//		MotionComponent motion_component = m.Get<MotionComponent>(id);
//		motion_component->torques.push_back(torque);
//	}
//
//	void AddTorque(glm::vec3 force, glm::vec3 distance) {
//		MotionComponent* motion_component = ECSEngine::component_manager().GetComponent<MotionComponent>(m_id);
//		Torque torque(force, distance);
//		motion_component->torques.push_back(torque);
//	}
//
//	void SetVelocity(glm::vec3 velocity) {
//	    MotionComponent* motion_component = ECSEngine::component_manager().GetComponent<MotionComponent>(m_id);
//	    motion_component->velocity = velocity;
//	}
};