#include <glm/gtc/matrix_transform.hpp>
#include "PhysicsSystem.h"

void LogVector(glm::vec3 v) {
	std::cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << std::endl;
}
void LogVector(glm::vec4 v) {
	std::cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << ", w: " << v.w << std::endl;
}
void LogMatrix(glm::mat4 m) {
	LogVector(m[0]);
	LogVector(m[1]);
	LogVector(m[2]);
	LogVector(m[3]);
}

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