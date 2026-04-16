#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec2 position;
    glm::mat4 viewMatrix;
    bool dirty;

    void updateView() {
        viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
        dirty = false;
    }

public:
    Camera() : position(0.0f, 0.0f), dirty(true) {}

    void setPosition(const glm::vec2& pos) {
        position = pos;
        dirty = true;
    }

    void move(glm::vec2 &delta) {
        position += delta;
        dirty = true;
    }

    const glm::vec2& getPosition() const {
        return position;
    }

    const glm::mat4& getViewMatrix() {
        if (dirty) {
            updateView();
        }
        return viewMatrix;
    }

    void update() {
        if (dirty) {
            updateView();
        }
    }
};