#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "player.h"
#include "projectile.h"

#define WINDOW_TITLE "dr.stop"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define MAX_PLAYERS 1
#define MAX_PROJECTILES 500
#define MAX_ENEMIES 100
#define FPS 60
#define MAX_BROADCASTS 5
// #define GRID_WIDTH 50
// #define GRID_HEIGHT 50
#define GAMEWORLD_SIZE 3000
#define BACKGROUND_COLOR (Color){ 200, 200, 200, 255 }

enum GAME_TEXTURES{
    TEXTURE_BLOCK,
    TEXTURE_BOARDER,
    TEXTURE_COUNT
};

enum WAVE_STATE{
    WAVE_STARTED,
    WAVE_COMPLITED,
    WAVE_WAITING
};
enum GAME_STATE{
    GAME_PLAYING,
    GAME_OVER,
    GAME_COUNT
};

typedef struct {
    Vector2 m_mousePosWorld;
    Camera2D m_cam;
    long int m_tick;
    unsigned int m_waveTick;
    unsigned int m_wave;
    unsigned long int m_numberOfPlayers;
    unsigned long int m_numberOfProjectiles;
    unsigned long int m_numberOfEnemys;
    unsigned long int m_numberOfTextBoxes;
    enum WAVE_STATE m_waveState;
    enum GAME_STATE m_gameState;
    Texture2D ma_textures[TEXTURE_COUNT];
    int m_screenWidth;
    int m_screenHeight;
}game_t;
game_t *getGameHandle();

Projectile_t *getProjectileByID(int ID);
Player_t *getPlayerByID(int ID);
void gameTick();
void gameInit();
void gameClose();
void gameReset();
void gameoverTick();

void loadGameData();

typedef struct{
    char *m_text;
    int m_duration;
    long int m_tick;
    int m_ID;
}t_broadcast;
void createBroadcast(char *text, int duration, int fontsize);
void distroyBroadcast(int ID);
void broadcastTick(t_broadcast *pbrod);
t_broadcast *getBroadcastByID(int ID);

#endif//GAME_H
