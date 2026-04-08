#pragma once

#include <ECS.h>
#include <ECS/Components/Position.h>

using namespace ECS;

class DebugSystem : public EntitySystem
{
public:
    virtual ~DebugSystem() {}

    virtual void tick(World* world, float deltaTime) override
    {
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        world->each<Position>([&](Entity* ent, ComponentHandle<Position> position) {  
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(position->x, 200.0f);
        });
        glEnd();
    }
};