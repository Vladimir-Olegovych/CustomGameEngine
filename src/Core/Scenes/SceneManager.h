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
    Scene* getCurrentScene() {
        if (currentScene >= 0 && currentScene < scenes.size()) {
            return scenes[currentScene].get();
        }
        return nullptr;
    }
    void addScene(std::unique_ptr<Scene> scene) {
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
    
    void update() {
        if (currentScene >= 0) scenes[currentScene]->update();
    }
    
    void render() {
        if (currentScene >= 0) scenes[currentScene]->render();
    }
    
    void handleInput(GLFWwindow* window) {
        if (currentScene >= 0) scenes[currentScene]->handleInput(window);
    }
};