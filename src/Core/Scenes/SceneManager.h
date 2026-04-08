#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <vector>
#include <Core/Scenes/Scene.h>

class SceneManager {
private:
    std::vector<std::unique_ptr<Scene>> scenes;
    int currentScene = -1;
    
public:
    void addScene(std::unique_ptr<Scene> scene) {
        scene.get()->onEnterApplication();
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
    
    void handleInput(GLFWwindow* window) {
        if (currentScene >= 0) scenes[currentScene]->handleInput(window);
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