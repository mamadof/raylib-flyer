#ifndef TEXTURE_H
#define TEXTURE_H
#include <raylib.h>


typedef enum {
    TEXTURE_BLOCK,
    TEXTURE_BOARDER,
    TEXTURE_COUNT
}GAME_TEXTURES;

void loadGameTexture();
void unloadGameTexture();
Texture2D getGameTexture(GAME_TEXTURES);
RenderTexture getWorldTexture();


#endif //TEXTURE_H