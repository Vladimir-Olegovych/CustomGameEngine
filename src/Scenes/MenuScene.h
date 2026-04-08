#include <GLFW/glfw3.h>
#include <memory>
#include <Core/Scenes/SceneManager.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class MenuScene : public Scene {
public:
    void onEnter() override {

    }
    
    void onExit() override {

    }
    
    void update() override {

    }
    
    void render() override {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Game Info", nullptr);
        ImGui::SetWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
        ImGui::Text("Menu Scene");
        ImGui::Text("Delta: %.0f", deltaTime);
        ImGui::Text("FPS: %.0f", io.Framerate);
        ImGui::Text("Window Size: %.0f x %.0f", io.DisplaySize.x, io.DisplaySize.y);
        ImGui::End();
    }
    
    void handleInput(GLFWwindow* window) override {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            
        }
    }
};