#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PlayerInput {
public:

    GLFWwindow* window;
    glm::vec2 move_vector2 = glm::vec2(0, 0);

    PlayerInput(GLFWwindow* window): window(window){}

    void update(float deltaTime) {
        updatePlayerMove(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

private:

    void updatePlayerMove(float deltaTime) {
        move_vector2.x = 0;
        move_vector2.y = 0;
        
        float speed = 500.0f * deltaTime;
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            move_vector2.y += speed;
        }
        
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            move_vector2.y -= speed;
        }
        
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            move_vector2.x -= speed;
        }
        
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            move_vector2.x += speed;
        }
        
        if (move_vector2.x != 0 && move_vector2.y != 0) {
            move_vector2 = move_vector2 * 0.7071f;
        }
    }
};