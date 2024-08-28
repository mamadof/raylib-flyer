#include "texture.h"
#include <raylib.h>

Texture2D ga_textures[TEXTURE_COUNT];

void loadGameTexture()
{
    ga_textures[TEXTURE_BLOCK] = LoadTexture("data/images/grid.png");
    ga_textures[TEXTURE_BOARDER] = LoadTexture("data/images/game_boarder.png");

}

void unloadGameTexture()
{
    for(int i = 0; i < TEXTURE_COUNT; i++)
    {
        UnloadTexture(ga_textures[i]);
    }
}

Texture2D getGameTexture(GAME_TEXTURES texture)
{
    return ga_textures[texture];
}
