#include "texture.h"
#include <raylib.h>
#include <raymath.h>
#include "game.h"

Texture2D ga_textures[TEXTURE_COUNT];
RenderTexture g_world;

void loadGameTexture()
{
    ga_textures[TEXTURE_BLOCK] = LoadTexture("data/images/grid.png");
    ga_textures[TEXTURE_BOARDER] = LoadTexture("data/images/game_boarder.png");

    g_world = LoadRenderTexture(GAMEWORLD_SIZE*2, GAMEWORLD_SIZE*2);//for drawing all the grids and boarders
    BeginTextureMode(g_world);
    ClearBackground(BACKGROUND_COLOR_2);
    //draw grid
    int distance;
    for(int x = 0; x < (GAMEWORLD_SIZE/getGameTexture(TEXTURE_BLOCK).width)*2; x++)
    {
        for(int y = 0; y < (GAMEWORLD_SIZE/getGameTexture(TEXTURE_BLOCK).height)*2; y++)
        {
            distance = Vector2Distance((Vector2){x,y}, (Vector2){(float)GAMEWORLD_SIZE/getGameTexture(TEXTURE_BLOCK).width,
            (float)GAMEWORLD_SIZE/getGameTexture(TEXTURE_BLOCK).height});
            DrawTexture(getGameTexture(TEXTURE_BLOCK),
            getGameTexture(TEXTURE_BLOCK).width*x,
            getGameTexture(TEXTURE_BLOCK).height*y,
            (Color){distance*2,distance*2,0,distance*2});
        }
    }
    //draw borders
    // int textureWidth = getGameTexture(TEXTURE_BOARDER).width;
    // int textureheight = getGameTexture(TEXTURE_BOARDER).height;
    // int xiter = GAMEWORLD_SIZE/textureWidth;
    // int yiter = GAMEWORLD_SIZE/textureheight;
    // for(int x = 0; x <= xiter; x++)
    // {
    //     for(int y = 0; y <= yiter; y++)
    //     {
    //         //draw boarder up and down
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), x*textureWidth, -GAMEWORLD_SIZE-textureheight, RED);
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), -x*textureWidth, -GAMEWORLD_SIZE-textureheight, RED);
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), x*textureWidth, GAMEWORLD_SIZE, RED);
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), -x*textureWidth, GAMEWORLD_SIZE, RED);
    //         //draw boarder left and right
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), -GAMEWORLD_SIZE-textureWidth, y*textureheight, RED);
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), -GAMEWORLD_SIZE-textureWidth, -y*textureheight-textureheight, RED);
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), GAMEWORLD_SIZE, y*textureheight, RED);
    //         DrawTexture(getGameTexture(TEXTURE_BOARDER), GAMEWORLD_SIZE, -y*textureheight, RED);
    //     }
    // }
    EndTextureMode();

}

void unloadGameTexture()
{
    for(int i = 0; i < TEXTURE_COUNT; i++)
    {
        UnloadTexture(ga_textures[i]);
    }
    UnloadRenderTexture(getWorldTexture());
}

Texture2D getGameTexture(GAME_TEXTURES texture)
{
    return ga_textures[texture];
}

RenderTexture getWorldTexture()
{
    return g_world;
}
