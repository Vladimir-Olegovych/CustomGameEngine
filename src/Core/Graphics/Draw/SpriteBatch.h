#pragma once

#include "shader.h"
#include "texture.h"
#include "Core/Graphics/Draw/Camera.h"
#include "VAO.h"
#include "VBO.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpriteBatch {
private:
    struct SpriteCommand {
        Texture* texture;
        float x, y;
        float width, height;
        float angle;
    };

    struct Vertex {
        glm::vec2 position;
        glm::vec2 texCoord;
    };

    struct DrawRange {
        Texture* texture;
        size_t startVertex;
        size_t vertexCount;
    };
    
    int screenWidth, screenHeight;
    Shader shader;
    VAO vao;
    std::unique_ptr<VBO> vbo;

    glm::mat4 projection;

    std::vector<SpriteCommand> commands;
    std::vector<DrawRange> ranges;

    void initBuffers() {
        vao.bind();
        vbo = std::make_unique<VBO>();

        vao.linkAttrib(*vbo, 0, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
        vao.linkAttrib(*vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

        vao.unbind();
        commands.reserve(1024);
    }

    static glm::vec2 rotatePoint(const glm::vec2& point, const glm::vec2& center, float angleRad) {
        float c = std::cos(angleRad);
        float s = std::sin(angleRad);
        glm::vec2 translated = point - center;
        glm::vec2 rotated;
        rotated.x = translated.x * c - translated.y * s;
        rotated.y = translated.x * s + translated.y * c;
        return rotated + center;
    }

    void buildVertexData(std::vector<Vertex>& outVertices, const SpriteCommand& cmd) {
        float x = cmd.x;
        float y = cmd.y;
        float w = cmd.width;
        float h = cmd.height;
        float cx = x + w * 0.5f;
        float cy = y + h * 0.5f;
        float angleRad = cmd.angle;

        glm::vec2 corners[4] = {
            {x,     y},
            {x + w, y},
            {x + w, y + h},
            {x,     y + h}
        };

        glm::vec2 rotated[4];
        for (int i = 0; i < 4; ++i) {
            rotated[i] = rotatePoint(corners[i], {cx, cy}, angleRad);
        }

        glm::vec2 texCoords[4] = {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        };

        outVertices.push_back({rotated[0], texCoords[0]});
        outVertices.push_back({rotated[1], texCoords[1]});
        outVertices.push_back({rotated[2], texCoords[2]});

        outVertices.push_back({rotated[2], texCoords[2]});
        outVertices.push_back({rotated[3], texCoords[3]});
        outVertices.push_back({rotated[0], texCoords[0]});
    }

    void flush() {
        if (commands.empty()) return;

        std::stable_sort(commands.begin(), commands.end(),
            [](const SpriteCommand& a, const SpriteCommand& b) {
                return a.texture < b.texture;
            });

        std::vector<Vertex> allVertices;
        ranges.clear();

        size_t i = 0;
        while (i < commands.size()) {
            Texture* currentTex = commands[i].texture;
            size_t startIdx = allVertices.size();

            while (i < commands.size() && commands[i].texture == currentTex) {
                buildVertexData(allVertices, commands[i]);
                ++i;
            }

            size_t vertexCount = allVertices.size() - startIdx;
            ranges.push_back({currentTex, startIdx, vertexCount});
        }

        vbo->bind();
        glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(Vertex),
                     allVertices.data(), GL_DYNAMIC_DRAW);

        vao.bind();
        for (const auto& range : ranges) {
            range.texture->bind();
            glDrawArrays(GL_TRIANGLES, range.startVertex, range.vertexCount);
        }
        vao.unbind();

        commands.clear();
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
        projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
        shader.activate();
        shader.setMat4("projection", projection);
        shader.setInt("tex0", 0);
    }

    void begin() {
        shader.activate();
        vao.bind();
        shader.setMat4("view", view);
    }

    void drawTexture(Texture& texture, float x, float y, float width, float height, float angle = 0.0f) {
        commands.push_back({&texture, x, y, width, height, angle});
    }

    void end() {
        flush();
    }

    void resize(float width, float height) {
        screenWidth = width;
        screenHeight = height;
        projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
        shader.activate();
        shader.setMat4("projection", projection);
    }

    void clear(){
        shader.remove();
    }

    ~SpriteBatch() = default;
};