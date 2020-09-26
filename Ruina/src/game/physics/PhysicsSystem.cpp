#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(SystemId id) : System(id) {
	SubscribeToEvent<OnGameTickEvent>();
}

void PhysicsSystem::Update(const Event &) {
	std::unordered_set<Component*> components = ECSEngine::component_manager().GetComponentGroup<MotionComponent>();
	float linear_scale = 0.005;
	float angular_scale = 0.01;
	for (Component* component : components) {
		auto* motion_component = (MotionComponent*)component;
		glm::vec3 net_linear(0);
		glm::vec3 net_torque(0);
		for (Torque torque : motion_component->torques) {
			net_linear += torque.force;
			net_torque += glm::cross(torque.force, torque.distance);
		}

		motion_component->velocity += linear_scale * net_linear;
		motion_component->angular_velocity = angular_scale * net_torque;
		motion_component->center += motion_component->velocity;
		float angular_speed = glm::length(motion_component->angular_velocity);

		auto* mesh_component = ECSEngine::component_manager().GetComponent<MeshComponent>(motion_component->m_entity_id);
		mesh_component->model = glm::translate(
			glm::rotate(mesh_component->model,
			angular_speed, motion_component->angular_velocity),
		motion_component->velocity);
	}
}