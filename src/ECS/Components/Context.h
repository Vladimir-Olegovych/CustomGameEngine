#pragma once

#include <GLFW/glfw3.h>

#include <Core/Scenes/SceneManager.h>

#include <Core/Player/PlayerInput.h>
#include <Core/Graphics/Draw/Camera.h>
#include <Core/Graphics/Draw/SpriteBatch.h>
#include <Core/Graphics/Texture/AssetManager.h>

struct Context
{
    GLFWwindow* window = nullptr;
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
        assetManager.clear();
        spriteBatch.clear();
        sceneManager.destroyScenes();
    }
};