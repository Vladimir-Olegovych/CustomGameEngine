#pragma once

class Context;

class Scene {
public:
    Context* context = nullptr;
    virtual ~Scene() = default;
    virtual void update(float deltaTime) = 0;
    virtual void onEnterApplication() = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onExitApplication() = 0;
    virtual void resize(int width, int height) = 0;
};