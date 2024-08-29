#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "render.h"
#include "player.h"
#include "projectile.h"
#include "enemy.h"
#include "world_interface.h"
#include "texture.h"
#include "sounds.h"


game_t g_game;
game_t *pgame = &g_game;
char g_text[200];
unsigned long int g_waveDuration;
static bool g_temp = false;

// int g_waveState;

void gameTick()
{
    ++pgame->m_tick;
    if(pgame->m_gameState == GAME_PLAYING)
    {
        for(int i = 0; i < MAX_PLAYERS; i++)
        {
            Player_t *pplayer;
            pplayer = getPlayerByID(i);
            if(pplayer == NULL)continue;
            playerTick(pplayer);
        }
        //iterate through all projectiles
        if(getNumberOfProjectiles() > 0)
            for(int i = 0; i < MAX_PROJECTILES; i++)
            {
            if(getProjectileByID(i) == NULL)continue; 
                projectileTick(getProjectileByID(i));
            }
        //text boxes tick
        for (int i = 0; i < TEXT_COUNT; i++)
        {
            textBox_t *ptext = getTextBoxByID(i);
            if(ptext == NULL || !ptext->m_show) continue;
            textBoxTick(ptext);
        }
        //wave control
        if(pgame->m_waveState == WAVE_STARTED)
        {
            if(pgame->m_waveTick < g_waveDuration && pgame->m_tick % 30 == 0 && getNumberOfEnemies() < MAX_ENEMIES)
            {
                createEnemy((Vector2){GetRandomValue(-GAMEWORLD_SIZE, GAMEWORLD_SIZE), GetRandomValue(-GAMEWORLD_SIZE, GAMEWORLD_SIZE)},
                (Vector2){GetRandomValue(-10, 10), GetRandomValue(-10, 10)});
                getTextBoxByID(TEXT_STARTWAVE)->m_show = false;
            }
            ++pgame->m_waveTick;
        }
        if(pgame->m_waveTick > 1000 && getNumberOfEnemies() == 0)pgame->m_waveState = WAVE_COMPLITED;

        if(pgame->m_waveState == WAVE_COMPLITED)
        {
            ++pgame->m_wave;
            sprintf(g_text, "start wave %d", pgame->m_wave+1);
            getTextBoxByID(TEXT_STARTWAVE)->m_text = g_text;
            getTextBoxByID(TEXT_STARTWAVE)->m_show = true;
            getPlayerByID(0)->m_money += 50 * pgame->m_wave;
            pgame->m_waveTick = 0;
            pgame->m_waveState = WAVE_WAITING;
        }
        if (pgame->m_waveState == WAVE_WAITING)
        {
            getTextBoxByID(TEXT_STARTWAVE)->m_show = true;
        }
        //iterate through all enemyies
        for(int i = 0; i < MAX_ENEMIES; i++)
        {
            enemy_t *penemy = getEnemyByID(i);
            if(penemy == NULL)continue; 
            EnemyTick(penemy);
            if(CheckCollisionPointCircle(getPlayerByID(0)->m_body[0],penemy->m_position, penemy->m_radios)||
            CheckCollisionPointCircle(getPlayerByID(0)->m_body[1],penemy->m_position, penemy->m_radios)||
            CheckCollisionPointCircle(getPlayerByID(0)->m_body[2],penemy->m_position, penemy->m_radios))
            getPlayerByID(0)->m_HP -= penemy->m_radios/8;
        }
    }else if(pgame->m_gameState == GAME_OVER){
        if(!g_temp)
        {
            createBroadcast("press r to retry\n", 1000, 50);  
            g_temp = true;
        }
    }
    for(int i = 0; i < MAX_BROADCASTS; i++)
    {
        t_broadcast *pbrod;
        pbrod = getBroadcastByID(i);
        if(pbrod == NULL)continue;
        broadcastTick(pbrod);
    }
    if(IsKeyPressed(KEY_R))gameReset();
    renderAll();

    // printf("player 0 pos: %f %f\n\n", getPlayerByID(0)->m_position.x, getPlayerByID(0)->m_position.y);
}

void gameInit()
{
    pgame->m_gameState = GAME_PLAYING;
    InitWindow(GetScreenWidth(), GetScreenHeight(), WINDOW_TITLE);
    InitAudioDevice();
    SetTargetFPS(FPS);
    //texture loading
    loadGameTexture();
    //load sounds
    loadGameSounds();
    //camera setup
    pgame->m_cam.offset = (Vector2){(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
    pgame->m_cam.rotation = 0;
    pgame->m_cam.zoom = 1.0f;
    //wave control
    pgame->m_waveState = WAVE_WAITING;
    g_waveDuration = 1000;
    pgame->m_waveTick = 0;
    //text boxes setup
    createTextBox("start wave", (Vector2){-400, -400}, 30, BLACK, TEXT_STARTWAVE);

    createPlayer();
}

game_t *getGameHandle()
{
    return pgame;
}

void gameReset()
{
    //remove all the players
    DistroyPlayer(-1);
    createPlayer();
    //remove all the projectiles
    distroyProjectile(-1);
    distroyBroadcast(-1);
    g_temp = false;
    pgame->m_tick = 0;
    pgame->m_gameState = GAME_PLAYING;
}

void gameClose()
{
    //free game stuff
    DistroyPlayer(-1);
    distroyProjectile(-1);
    distroyEnemy(-1);
    distroyBroadcast(-1);

    //free raylib stuff
    unloadGameTexture();
    CloseAudioDevice();
    CloseWindow();
}