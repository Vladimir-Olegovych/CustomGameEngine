#pragma once

#include <fmt/core.h>

#include <ECS.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <ECS/Systems/DrawSystem.h>
#include <ECS/Components/Context.h>

using namespace ECS;

class MenuScene : public Scene {
    private:
        World* world;
    public:

    void onEnterApplication() override {
        world = World::createWorld();

        DrawSystem* drawSystem = new DrawSystem(context);
        world->registerSystem(drawSystem);
    }

    void onExitApplication() override {
        world->destroyWorld();
        world = nullptr;
    }

    void onEnter() override {}
    
    void onExit() override {}

    void update(float deltaTime) override {
        context->playerInput.update(deltaTime);
        world->tick(deltaTime);
    }
    void resize(int width, int height) override {
        Context& context_ref = *context;
        glViewport(0, 0, width, height);
        context_ref.spriteBatch.resize(width, height);
        
        fmt::println("Width: {}, Height: {}", width, height);
    }
};