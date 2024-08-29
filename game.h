#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "player.h"
#include "projectile.h"

#define WINDOW_TITLE "flyer"
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
#define BACKGROUND_COLOR (Color){ 100, 100, 120, 255 }
#define BACKGROUND_COLOR_2 (Color){ 200, 200, 200, 255 }

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
    long int m_tick;
    unsigned int m_waveTick;
    unsigned int m_wave;
    Camera2D m_cam;
    enum WAVE_STATE m_waveState;
    enum GAME_STATE m_gameState;
}game_t;
game_t *getGameHandle();

void gameTick();
void gameInit();
void gameClose();
void gameReset();
void gameoverTick();
void loadGameData();

#endif//GAME_H
