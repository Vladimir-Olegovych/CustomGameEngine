#pragma once

#include <texture.h>

struct TextureComponent
{
    TextureComponent(Texture* texture = nullptr): texture(texture) {}
    Texture* texture = nullptr;
};