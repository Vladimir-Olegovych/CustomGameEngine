#pragma once

#include <GLFW/glfw3.h>

#include <server/ServerMachine.h>
#include <app/Core/Scenes/SceneManager.h>

#include <app/Core/Player/PlayerInput.h>
#include <app/Core/Graphics/Draw/Camera.h>
#include <app/Core/Graphics/Draw/SpriteBatch.h>
#include <app/Core/Graphics/Texture/AssetManager.h>

struct Context
{
    GLFWwindow* window = nullptr;
    ServerMachine serverMachine = ServerMachine();
    Camera camera = Camera();
    PlayerInput playerInput;
    SceneManager sceneManager;
    AssetManager assetManager = AssetManager();
    SpriteBatch spriteBatch = SpriteBatch(0, 0);

    Context(GLFWwindow* window): sceneManager(SceneManager(this, window))
                               , playerInput(PlayerInput(window))
    {
        this->window = window;
    }

    void clear(){
        serverMachine.stopServer();
        assetManager.clear();
        spriteBatch.clear();
        sceneManager.destroyScenes();
    }
};