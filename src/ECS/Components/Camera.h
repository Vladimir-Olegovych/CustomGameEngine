#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera {
    glm::vec3 Position = glm::vec3(0.0f, 2.0f, 5.0f);
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    float Yaw = -90.0f;
    float Pitch = 0.0f;
    float Speed = 2.5f;
    float Sensitivity = 0.1f;
    
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }
};