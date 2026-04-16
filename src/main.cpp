#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <Core/Scenes/SceneManager.h>
#include <Scenes/MenuScene.h>
#include <Core/Graphics/Texture/AssetManager.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <thread>
#include <chrono>

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1200, 800, "Scene Demo", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
        if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    float refreshHz = mode->refreshRate;
    const float FIXED_DT = 1.0f / refreshHz;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DeltaTime = FIXED_DT;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Включить навигацию с клавиатуры
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Включить docking (если используете docking-ветку)
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    AssetManager& assetManager = AssetManager::getInstance();

    assetManager.loadTexture("gravel", "resources/textures/gravel_001_basecolor.jpg");
    assetManager.loadTexture("wall", "resources/textures/concrete_wall_016_basecolor.png");

    SceneManager sceneManager;
    sceneManager.addScene(std::make_unique<MenuScene>());
    sceneManager.setScene(0);

    double frameStartTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double frameEndTime = glfwGetTime();
        float frameDeltaTime = static_cast<float>(frameEndTime - frameStartTime);
        frameStartTime = frameEndTime;

        if (frameDeltaTime > 0.1f) frameDeltaTime = 0.1f;

        sceneManager.handleInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        sceneManager.update(frameDeltaTime);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
        
        double fullCycleTime = glfwGetTime() - frameStartTime;
        double sleepTimeMs = (FIXED_DT) - fullCycleTime;
        if (sleepTimeMs > 0.0) {
            std::this_thread::sleep_for(std::chrono::duration<double>(sleepTimeMs));
        }
    }
    
    sceneManager.destroyScenes();

    assetManager.clear();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}