#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <Core/Scenes/Scene.h>
#include <ECS/Components/Context.h>

class SceneManager {
private:
    std::vector<std::unique_ptr<Scene>> scenes;
    int currentScene = -1;
    Context* context;
    GLFWwindow* window;
public:
    SceneManager(Context* context, GLFWwindow* window): context(context), window(window) {}

    void addScene(std::unique_ptr<Scene> scene) {
        Scene& scene_ref = *scene.get();

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        scene_ref.context = context;
        scene_ref.onEnterApplication();
        scene_ref.resize(width, height);
        scenes.push_back(std::move(scene));
    }
    
    void setScene(int index) {
        if (currentScene >= 0 && currentScene < scenes.size()) {
            scenes[currentScene]->onExit();
        }
        currentScene = index;
        if (currentScene >= 0 && currentScene < scenes.size()) {
            scenes[currentScene]->onEnter();
        }
    }
    
    void update(float deltaTime) {
        if (currentScene >= 0) scenes[currentScene]->update(deltaTime);
    }

    void resize(int width, int height) {
        if (currentScene >= 0) scenes[currentScene]->resize(width, height);
    }

    void destroyScenes() {
        if (currentScene >= 0) scenes[currentScene]->onExit();
        for (auto& scene : scenes) {
            if (scene) {
                scene->onExitApplication();
            }
        }
        scenes.clear();
        currentScene = -1;
    }
};