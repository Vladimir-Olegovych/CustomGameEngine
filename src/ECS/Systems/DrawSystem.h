#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <shader.h>
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
    Shader shaderProgram = Shader("src/Resources/Shaders/default.vert", "src/Resources/Shaders/default.frag");
    VAO VAO1 = VAO();
    public:
    int cameraId = 0;
    void configure(World* world)
	{
        try {
        GLfloat vertices[] = {
            // COORDINATE / COLORS //
            -0.5f, 0.5f, 0.0f, 0.0f, 128 / 255.0f, 255 / 255.0f,
            0.5f, 0.5f, 0.0f, 255 / 255.0f, 0 / 255.0f, 0 / 255.0f,
            0.5f, -0.5f, 0.0f, 0 / 255.0f, 153 / 255.0f, 0 / 255.0f,
            -0.5f, -0.5f, 0.0f, 255 / 255.0f, 255 / 255.0f, 51 / 255.0f
        };
        GLuint indexes[] = { 0, 1, 2, 3};
        VAO1.bind();
        VBO VBO1(vertices, sizeof(vertices));
        EBO EBO1(indexes, sizeof(indexes));
        VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
        VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 *
        sizeof(float)));
        VAO1.unbind();
        VBO1.unbind();
        EBO1.unbind();
        glViewport(0, 0, 800, 800);
        } catch (int e) {
            std::cout << "ПЕРЕХВАЧЕНО ИСКЛЮЧЕНИЕ INT в configure: " << e << std::endl;
            throw;
        }
	}

    virtual void tick(World* world, float deltaTime) override
    {
        /*
        Entity* c_ent = world->getByIndex(cameraId);
        ComponentHandle<Camera> camera = c_ent->get<Camera>();
        */

        shaderProgram.activate();
        //Скажем OpenGL использовать VBO
        VAO1.bind();
        // Скажем OpenGL нарисовать фигуру с 4 вершинами
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);
        /*
        world->each<Position>([&](Entity* ent, ComponentHandle<Position> position) {  
            
        });
        */
    }
};