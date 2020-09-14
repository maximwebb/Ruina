#pragma once
#include "glm/gtc/matrix_transform.hpp"
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

	void SetProjectionMatrix(glm::mat4 proj);

private:
    void UpdateViewMatrix();
    void IncrementAbsolutePosition(float x, float y, float z);

public:
    glm::mat4 m_view_matrix;
    glm::mat4 m_proj_matrix;

private:
    glm::vec3 m_position;
    float m_pitch;
    float m_yaw;
    const float m_initial_yaw;
    glm::vec3 m_camera_target;
    glm::mat4 m_yaw_rotation_matrix;
};