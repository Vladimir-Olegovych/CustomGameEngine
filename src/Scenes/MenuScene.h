#pragma once

#include <ECS.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ECS/Systems/DrawSystem.h>

#include <ECS/Components/Camera.h>
#include <ECS/Components/Position.h>

using namespace ECS;

class MenuScene : public Scene {
    private:
        World* world;
    public:

    void onEnterApplication() override {
        world = World::createWorld();

        Entity* c_ent = world->create();
        c_ent->assign<Camera>();

        DrawSystem* drawSystem = new DrawSystem();
        drawSystem->cameraId = c_ent->getEntityId();
        world->registerSystem(drawSystem);

        for(int i = 2; i < 15; i++){
            Entity* ent = world->create();
            ent->assign<Position>(0.f + i * 20, 0.f, 0.f);
        }
        
    }

    void onExitApplication() override {
        world->destroyWorld();
        world = nullptr;
    }

    void onEnter() override {}
    
    void onExit() override {}

    void update(float deltaTime) override {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Game Info", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
        ImGui::Text("Menu Scene");
        ImGui::Text("Delta: %.003f", deltaTime);
        ImGui::Text("FPS: %.0f", io.Framerate);
        ImGui::Text("Window Size: %.0f x %.0f", io.DisplaySize.x, io.DisplaySize.y);
        ImGui::End();

        world->tick(deltaTime);
    }
    
    void handleInput(GLFWwindow* window) override {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
};