#pragma once

struct Position
{
    Position(float x, float y) : x(x), y(y) {}
    Position() : x(0.f), y(0.f) {}

    float x;
    float y;
};