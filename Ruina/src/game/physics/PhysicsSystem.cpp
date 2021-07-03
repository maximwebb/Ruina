#include "MassComponent.h"
#include "MeshComponent.h"
#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem(Manager& m) : System(m) {
    Subscribe<GameTickEvent>(HANDLER(Update));
}

// TODO: Separate mass member out of motion
void PhysicsSystem::Update(const Event&) {
    static float linear_scale = 0.005;
    static float angular_scale = 0.01;

    auto mass_motion_mesh_group = m.CreateGroup<MassComponent, MotionComponent, MeshComponent>();
    auto gravity_group = m.CreateGroup<MassComponent, MotionComponent, GravityComponent>();

    for (auto e1 : gravity_group) {
        glm::vec3 net_linear(0);
        auto [mass1, motion1, gravity1] = gravity_group.Get(e1);
        for (auto e2 : gravity_group) {
            auto [mass2, motion2, gravity2] = gravity_group.Get(e2);
            if (e1 != e2) {
                net_linear += CalculateGravity(mass1->mass, mass2->mass, motion1->center, motion2->center);
            }
        }
        motion1->velocity += linear_scale * (net_linear/motion1->mass);
    }

    for (auto e : mass_motion_mesh_group) {
        auto [mass, motion, mesh] = mass_motion_mesh_group.Get(e);
        glm::vec3 net_linear(0);
        glm::vec3 net_torque(0);

        for (Torque torque : motion->torques) {
            net_linear += torque.force;
            net_torque += glm::cross(torque.force, torque.distance);
        }

        motion->velocity += linear_scale * (net_linear/motion->mass);
        motion->angular_velocity = angular_scale * net_torque;
        motion->center += motion->velocity;
        float angular_speed = glm::length(motion->angular_velocity);

        if (abs(angular_speed) < FLT_EPSILON) {
            mesh->model = glm::translate(mesh->model, motion->velocity);
        } else {
            mesh->model = glm::translate(
                    glm::rotate(mesh->model,
                                angular_speed, motion->angular_velocity),
                    motion->velocity);
        }
    }
}


glm::vec3 PhysicsSystem::CalculateGravity(float mass, float mass_other, glm::vec3 center, glm::vec3 center_other) {
    static float G = 0.01f;
    float radius = glm::length(center_other - center);
    if (radius < 2) {
        return glm::vec3(0);
    }
    else {
        return G * mass * mass_other * glm::normalize(center_other - center) * (1.0f/(radius*radius));
    }
};