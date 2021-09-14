#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"

float PI = 3.14159265f;

Camera::Camera(float x, float y, float z, float pitch, float yaw)
    : pitch(pitch), yaw(yaw), initial_yaw(yaw), position(x, y, z), view_matrix(1.0f), camera_target(0.0f),
      yaw_rotation_matrix(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f))) {
    UpdateViewMatrix();
    /* Default projection */
    proj_matrix = glm::perspective(1.0f, 4.0f / 3.0f, 1.0f, 150.0f);
}

Camera::~Camera() {

}

glm::vec4 Camera::GetPosition() {
	return glm::vec4(position, 1.0f);
}

void Camera::SetPosition(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
    UpdateViewMatrix();
}

void Camera::IncrementPosition(float x, float y, float z) {
    glm::vec3 rotated_pos = yaw_rotation_matrix * glm::vec4(x, y, z, 1);
    position.x += rotated_pos.x;
    position.y += rotated_pos.y;
    position.z += rotated_pos.z;
    UpdateViewMatrix();
}

void Camera::IncrementAbsolutePosition(float x, float y, float z) {
    position.x += x;
    position.y += y;
    position.z += z;
    UpdateViewMatrix();
}

void Camera::SetYaw(float _yaw) {
    yaw = _yaw;
    UpdateViewMatrix();
}

void Camera::IncrementYaw(float _yaw) {
    yaw += _yaw;
    UpdateViewMatrix();
}

void Camera::SetPitch(float _pitch) {
    pitch = _pitch;
    if (pitch > PI / 2) {
        pitch = PI / 2;
    }
    else if (pitch < -PI / 2) {
        pitch = -PI / 2;
    }
    UpdateViewMatrix();
}

void Camera::IncrementPitch(float _pitch) {
    if (pitch + _pitch < PI / 2 && pitch + _pitch > -PI / 2) {
        pitch += _pitch;
    }
    UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
    camera_target.x = cos(pitch) * cos(yaw) + position.x;
    camera_target.y = sin(pitch) + position.y;
    camera_target.z = cos(pitch) * sin(yaw) + position.z;
    view_matrix = glm::lookAt(position, camera_target, glm::vec3(0.0f, 1.0f, 0.0f));
    yaw_rotation_matrix = glm::rotate(glm::mat4(1.0f), initial_yaw - yaw, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::SetProjectionMatrix(glm::mat4 proj) {
    proj_matrix = proj;
}