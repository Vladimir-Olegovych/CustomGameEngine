#pragma once

#include <ECS.h>
#include <ECS/Components/Position.h>
#include <ECS/Components/Size.h>
#include <ECS/Components/TextureComponent.h>
#include <ECS/Components/Context.h>

#include <texture.h>
#include <Resources/TextureData.h>
#include <Core/Player/PlayerInput.h>
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
    PlayerInput& playerInput;
    AssetManager& assetManager;
    SpriteBatch& spriteBatch;
public:    
      DrawSystem(Context* context) 
        : context(context)
        , camera(context->camera)
        , spriteBatch(context->spriteBatch)
        , assetManager(context->assetManager)
        , playerInput(context->playerInput)
        {}
    void configure(World* world)
	{
        for (int i = 0; i < TextureData::COUNT; i++) {
            assetManager.loadTexture(
                keyTexture(static_cast<TextureData>(i)), 
                texturePaths[i]
            );
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

        camera.move(playerInput.move_vector2);
        camera.update();

        spriteBatch.view = camera.getViewMatrix();
        spriteBatch.begin();
        world->each<TextureComponent, Position, Size>([&](Entity* ent, 
            ComponentHandle<TextureComponent> textureComponent, 
            ComponentHandle<Position> position,
            ComponentHandle<Size> size) {
    
            spriteBatch.drawTexture(
                *textureComponent->texture,
                position->x, position->y, 
                size->w, size->h
            );
        });
        spriteBatch.end();
    }
};