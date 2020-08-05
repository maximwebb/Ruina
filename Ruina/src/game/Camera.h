#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    Camera(float, float, float, float, float);
    ~Camera();

    void SetPosition(float, float, float);
    void IncrementPosition(float, float, float);

    void SetPitch(float);
    void IncrementPitch(float);
    void SetYaw(float);
    void IncrementYaw(float);

private:
    void UpdateViewMatrix();
    void IncrementAbsolutePosition(float x, float y, float z);

public:
    glm::mat4 m_view_matrix;

private:
    glm::vec3 m_position;
    float m_pitch;
    float m_yaw;
    const float m_initial_yaw;
    glm::vec3 m_camera_target;
    glm::mat4 m_yaw_rotation_matrix;
};