#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"

float PI = 3.14159265f;

Camera::Camera(float x, float y, float z, float pitch, float yaw)
    : m_pitch(pitch), m_yaw(yaw), m_initial_yaw(yaw), m_position(x, y, z), m_view_matrix(1.0f), m_camera_target(0.0f),
    m_yaw_rotation_matrix(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f))) {
    UpdateViewMatrix();
}

Camera::~Camera() {
    std::cout << "Camera deleted" << std::endl;
}

void Camera::SetPosition(float x, float y, float z) {
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
    UpdateViewMatrix();
}

void Camera::IncrementPosition(float x, float y, float z) {
    glm::vec3 rotated_pos = m_yaw_rotation_matrix * glm::vec4(x, y, z, 1);
    m_position.x += rotated_pos.x;
    m_position.y += rotated_pos.y;
    m_position.z += rotated_pos.z;
    UpdateViewMatrix();
}

void Camera::IncrementAbsolutePosition(float x, float y, float z) {
    m_position.x += x;
    m_position.y += y;
    m_position.z += z;
    UpdateViewMatrix();
}

void Camera::SetYaw(float yaw) {
    m_yaw = yaw;
    UpdateViewMatrix();
}

void Camera::IncrementYaw(float yaw) {
    m_yaw += yaw;
    UpdateViewMatrix();
}

void Camera::SetPitch(float pitch) {
    m_pitch = pitch;
    if (m_pitch > PI/2) {
        m_pitch = PI/2;
    }
    else if (m_pitch < -PI/2) {
        m_pitch = -PI/2;
    }
    UpdateViewMatrix();
}

void Camera::IncrementPitch(float pitch) {
    if (m_pitch + pitch < PI/2 && m_pitch + pitch > -PI/2) {
        m_pitch += pitch;
    }
    UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
    m_camera_target.x = cos(m_pitch) * cos(m_yaw) + m_position.x;
    m_camera_target.y = sin(m_pitch) + m_position.y;
    m_camera_target.z = cos(m_pitch) * sin(m_yaw) + m_position.z;
    m_view_matrix = glm::lookAt(m_position, m_camera_target, glm::vec3(0.0f, 1.0f, 0.0f));
    m_yaw_rotation_matrix = glm::rotate(glm::mat4(1.0f), m_initial_yaw - m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
}
