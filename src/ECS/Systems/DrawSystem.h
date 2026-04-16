#pragma once

#include <texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ECS.h>
#include <ECS/Components/Position.h>

#include <Core/Graphics/Texture/AssetManager.h>
#include <Core/Graphics/Draw/SpriteBatch.h>
#include <Core/Graphics/Draw/Camera.h>

using namespace ECS;

class DrawSystem : public EntitySystem
{
    private:
    AssetManager& assetManager = AssetManager::getInstance();
    SpriteBatch spriteBatch = SpriteBatch(1200, 800);
    Camera camera = Camera();
    glm::vec2 v = glm::vec2(2.0f, 0.0f);
    Texture& texture = assetManager.getTexture("gravel");

    public:
    void configure(World* world)
	{
        glViewport(0, 0, 1200, 800);


        for(int x = 0; x < 40; x++){
            for(int y = 0; y < 8; y++){
                Entity* ent = world->create();
                ent->assign<Position>(x * 200, y * 200);
            }
        }
	}

    virtual void tick(World* world, float deltaTime) override
    {
        camera.move(v);
        camera.update();

        spriteBatch.view = camera.getViewMatrix();
        spriteBatch.begin();
        world->each<Position>([&](Entity* ent, ComponentHandle<Position> position) {
            spriteBatch.drawTexture(texture, position->x, position->y, 200, 200);
        });
        spriteBatch.end();
    }
};