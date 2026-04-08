#pragma once

#include <GLFW/glfw3.h>

class Scene {
public:
    float deltaTime = 0;
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleInput(GLFWwindow* window) = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
};