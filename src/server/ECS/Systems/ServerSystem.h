#pragma once

#include <ECS.h>
#include <fmt/core.h>

using namespace ECS;

class ServerSystem : public EntitySystem
{
    public:
    ServerSystem() {}
    
    void configure(World* world)
	{
        
	}

    virtual void tick(World* world, float deltaTime) override
    {
        fmt::println("Server tick");
    }
};