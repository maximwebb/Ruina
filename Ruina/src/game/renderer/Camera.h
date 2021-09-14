#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

class Camera {
public:
    Camera(float, float, float, float, float);
    ~Camera();

	glm::vec4 GetPosition();
	void SetPosition(float, float, float);
    void IncrementPosition(float, float, float);

    void SetPitch(float);
    void IncrementPitch(float);
    void SetYaw(float);
    void IncrementYaw(float);

	void SetProjectionMatrix(glm::mat4 proj);

	glm::mat4 view_matrix;
    glm::mat4 proj_matrix;

private:
    void UpdateViewMatrix();
    void IncrementAbsolutePosition(float x, float y, float z);

    glm::vec3 position;
    float pitch;
    float yaw;
    const float initial_yaw;
    glm::vec3 camera_target;
    glm::mat4 yaw_rotation_matrix;
};