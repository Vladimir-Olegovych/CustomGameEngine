#pragma once

enum TextureData {
    GRAVEL,
    WALL,
    COUNT
};

const char* texturePaths[] = {
    "resources/textures/gravel_001_basecolor.jpg",
    "resources/textures/concrete_wall_016_basecolor.png"
};

static const char * EnumStrings[] = { "GRAVEL", "WALL" };

const char * keyTexture(int enumVal)
{
  return EnumStrings[enumVal];
}