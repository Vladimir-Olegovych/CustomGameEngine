#pragma once

#include <ECS.h>
#include <ECS/Components/Position.h>
#include <ECS/Components/Size.h>
#include <ECS/Components/TextureComponent.h>
#include <ECS/Components/Context.h>

#include <texture.h>
#include <Resources/TextureData.h>
#include <Core/Graphics/Texture/AssetManager.h>
#include <Core/Graphics/Draw/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*
std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<int> texChoice(0, 1);
if(texChoice(gen) == 0) continue;
*/
using namespace ECS;

class ChunkSystem : public EntitySystem
{
private:
    Context* context;
    Camera& camera;
    AssetManager& assetManager;
public:    
    ChunkSystem(Context* context) 
    : context(context)
    , camera(context->camera)
    , assetManager(context->assetManager)
    {}

    void configure(World* world)
	{
        for(int x = -4; x < 4; x++){
            for(int y = -4; y < 4; y++){
                Entity* ent = world->create();
                auto textureComponent = ent->assign<TextureComponent>();
                auto size = ent->assign<Size>(500.f, 500.f);
                auto position = ent->assign<Position>(x * size->w, y * size->h);

                textureComponent->texture = &assetManager.getTexture(keyTexture(TextureData::GRAVEL));
            }
        }
        for(int x = 4; x < 8; x++){
            for(int y = -4; y < 4; y++){
                Entity* ent = world->create();
                auto textureComponent = ent->assign<TextureComponent>();
                auto size = ent->assign<Size>(500.f, 500.f);
                auto position = ent->assign<Position>(x * size->w, y * size->h);

                textureComponent->texture = &assetManager.getTexture(keyTexture(TextureData::WALL));
            }
        }
	}
    virtual void tick(World* world, float deltaTime) override
    {

    }
};