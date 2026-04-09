#pragma once

struct Position
{
    Position(float x, float y, float z) : x(x), y(y), z(z) {}
    Position() : x(0.f), y(0.f), z(0.f) {}

    float x;
    float y;
    float z;
};