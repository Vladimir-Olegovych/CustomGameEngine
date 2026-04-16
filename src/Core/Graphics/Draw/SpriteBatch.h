// SpriteBatch.h
#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Core/Graphics/Draw/Camera.h"

class SpriteBatch {
    private:
    Shader shader;
    VAO vao;
    std::unique_ptr<VBO> vbo;
    std::unique_ptr<EBO> ebo;
    glm::mat4 projection;
    int screenWidth, screenHeight;

    void initBuffers() {
        float vertices[] = {
            -0.5f,  0.5f, 0.0f,    0.0f, 1.0f,
             0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,    0.0f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        vao.bind();

        vbo = std::make_unique<VBO>(vertices, sizeof(vertices));
        ebo = std::make_unique<EBO>(indices, sizeof(indices));

        vao.linkAttrib(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
        vao.linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        vao.unbind();
    }

    public:
    glm::mat4 view = glm::mat4(1.0f);

    SpriteBatch(float width, float height, 
                const std::string& vertPath = "resources/shaders/sprite.vert",
                const std::string& fragPath = "resources/shaders/sprite.frag")
        : screenWidth(width), screenHeight(height),
          shader(vertPath.c_str(), fragPath.c_str())
    {
        initBuffers();
        projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
        shader.activate();
        shader.setMat4("projection", projection);
        shader.setInt("tex0", 0);
    }

    void begin(){
        shader.activate();
        vao.bind();
        shader.setMat4("view", view);
    }

    void drawTexture(Texture& texture, float x, float y, float width, float height) {
        texture.bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x + width/2.0f, y + height/2.0f, 0.0f));
        model = glm::scale(model, glm::vec3(width, height, 1.0f));
        shader.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        texture.unbind();
    }

    void end(){
        vao.unbind();
    }

    void resize(float width, float height) {
        screenWidth = width;
        screenHeight = height;
        projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
        shader.activate();
        shader.setMat4("projection", projection);
    }

    ~SpriteBatch() = default;
};