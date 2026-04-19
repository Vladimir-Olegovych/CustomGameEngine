#pragma once

#include <ECS.h>
#include <ECS/Components/Position.h>
#include <ECS/Components/Context.h>

#include <texture.h>
#include <Core/Graphics/Texture/AssetManager.h>
#include <Core/Graphics/Draw/SpriteBatch.h>
#include <Core/Graphics/Draw/Camera.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace ECS;

class DrawSystem : public EntitySystem
{
private:
    Context* context;
    Camera& camera;
    AssetManager& assetManager;
    SpriteBatch& spriteBatch;
    Texture* texture = nullptr;
public:    
      DrawSystem(Context* context) 
        : context(context)
        , camera(context->camera)
        , spriteBatch(context->spriteBatch)
        , assetManager(context->assetManager)
        {}
    void configure(World* world)
	{
        assetManager.loadTexture("gravel", "resources/textures/gravel_001_basecolor.jpg");
        assetManager.loadTexture("wall", "resources/textures/concrete_wall_016_basecolor.png");

        texture = &assetManager.getTexture("gravel");

        for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++){
                Entity* ent = world->create();
                ent->assign<Position>(x * 500, y * 500);
            }
        }
	}

    virtual void tick(World* world, float deltaTime) override
    {
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

        camera.move(context->playerInput.move_vector2);
        camera.update();

        spriteBatch.view = camera.getViewMatrix();
        spriteBatch.begin();
        world->each<Position>([&](Entity* ent, ComponentHandle<Position> position) {
            spriteBatch.drawTexture(*texture, position->x, position->y, 500, 500);
        });
        spriteBatch.end();
    }
};