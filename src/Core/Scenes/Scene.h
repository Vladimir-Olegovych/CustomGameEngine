#pragma once

#include <GLFW/glfw3.h>

class Scene {
public:
    virtual ~Scene() = default;
    virtual void update(float deltaTime) = 0;
    virtual void handleInput(GLFWwindow* window) = 0;
    virtual void onEnterApplication() = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onExitApplication() = 0;
};