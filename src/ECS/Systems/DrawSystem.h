#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <shader.h>
#include <texture.h>

#include <EBO.h>
#include <VAO.h>
#include <VBO.h>

#include <ECS.h>
#include <ECS/Components/Position.h>
#include <ECS/Components/Camera.h>
#include <glm/glm.hpp>

using namespace ECS;

class DrawSystem : public EntitySystem
{
    private:
    Shader shaderProgram = Shader("resources/shaders/default.vert", "resources/shaders/default.frag");
    VAO VAO1 = VAO();
    GLfloat vertices[32] = {
        // COORDINATE       COLORS                                       TEXTURE COORDINATE
        -0.5f, 0.5f, 0.0f,   0.0f, 128 / 255.0f, 255 / 255.0f,            0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,   255 / 255.0f, 0 / 255.0f, 0 / 255.0f,        0.0f, 1.0f,
        0.5f,-0.5f, 0.0f,   0 / 255.0f, 153 / 255.0f, 0 / 255.0f,        1.0f, 1.0f,
        -0.5f,-0.5f, 0.0f,   255 / 255.0f, 255 / 255.0f, 51 / 255.0f,     1.0f, 0.0f
    };

    Texture g_texture = Texture("resources/textures/gravel_001_basecolor.jpg", GL_TEXTURE_2D, 
                                                                               GL_TEXTURE0, 
                                                                               GL_RGB, 
                                                                               GL_UNSIGNED_BYTE
                                                                            );
    public:
    int cameraId = 0;
    void configure(World* world)
	{
        GLuint indexes[] = { 
            0, 1, 2,
            0, 2, 3
        };
        VAO1.bind();
        VBO VBO1(vertices, sizeof(vertices));
        EBO EBO1(indexes, sizeof(indexes));

        VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
        VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 *
        sizeof(float)));
        VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 *
        sizeof(float)));

        VAO1.unbind();
        VBO1.unbind();
        EBO1.unbind();

        g_texture.texUnit(shaderProgram, "tex0", 0);

        glViewport(0, 0, 1200, 800);
	}

    virtual void tick(World* world, float deltaTime) override
    {
        shaderProgram.activate();
        g_texture.bind();
        VAO1.bind();

        int uni_loc = glGetUniformLocation(shaderProgram.ID, "scr_aspect");
        glUniform1f(uni_loc, 800.f / 1200.f);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    ~DrawSystem() {
        g_texture.clear();
    }
};