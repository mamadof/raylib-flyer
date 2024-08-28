#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "render.h"
#include "player.h"
#include "projectile.h"
#include "enemy.h"
#include "world_interface.h"

extern Player_t *ga_pplayers[];
extern Projectile_t *ga_pprojectiles[];
extern enemy_t *ga_pEnemys[];
t_broadcast *ga_pbroadCasts[MAX_BROADCASTS];

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
        if(pgame->m_numberOfProjectiles > 0)
            for(int i = 0; i < MAX_PROJECTILES; i++)
            {
            if(ga_pprojectiles[i] == NULL)continue; 
                projectileTick(ga_pprojectiles[i]);
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
            if(pgame->m_waveTick < g_waveDuration && pgame->m_tick % 30 == 0 && pgame->m_numberOfEnemys < MAX_ENEMIES)
            {
                createEnemy((Vector2){GetRandomValue(-GAMEWORLD_SIZE, GAMEWORLD_SIZE), GetRandomValue(-GAMEWORLD_SIZE, GAMEWORLD_SIZE)},
                (Vector2){GetRandomValue(-10, 10), GetRandomValue(-10, 10)});
                getTextBoxByID(TEXT_STARTWAVE)->m_show = false;
            }
            ++pgame->m_waveTick;
        }
        if(pgame->m_waveTick > 1000 && pgame->m_numberOfEnemys == 0)pgame->m_waveState = WAVE_COMPLITED;

        if(pgame->m_waveState == WAVE_COMPLITED)
        {
            ++pgame->m_wave;
            sprintf(g_text, "start wave %d", pgame->m_wave+1);
            getTextBoxByID(TEXT_STARTWAVE)->m_text = g_text;
            getTextBoxByID(TEXT_STARTWAVE)->m_show = true;
            ga_pplayers[0]->m_money += 50 * pgame->m_wave;
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
            createBroadcast("press r to retry\n", 200, 50);  
            g_temp = true;
        }
    }
    if(IsKeyPressed(KEY_R))gameReset();
    for(int i = 0; i < MAX_BROADCASTS; i++)
    {
        t_broadcast *pbrod;
        pbrod = ga_pbroadCasts[i];
        if(pbrod == NULL)continue;
        broadcastTick(pbrod);
    }
    renderAll();

    // printf("player 0 pos: %f %f\n\n", ga_pplayers[0]->m_position.x, ga_pplayers[0]->m_position.y);
}

void gameInit()
{
    pgame->m_gameState = GAME_PLAYING;
    pgame->m_numberOfPlayers = 0;
    pgame->m_screenWidth = GetScreenWidth();
    pgame->m_screenHeight = GetScreenHeight();
    InitWindow(GetScreenWidth(), GetScreenHeight(), WINDOW_TITLE);
    InitAudioDevice();
    SetTargetFPS(FPS);
    //texture loading
    pgame->ma_textures[TEXTURE_BLOCK] = LoadTexture("data/images/grid.png");
    pgame->ma_textures[TEXTURE_BOARDER] = LoadTexture("data/images/game_boarder.png");
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
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        free(ga_pplayers[i]);
        ga_pplayers[i] = NULL;
    }
    pgame->m_numberOfPlayers = 0;
    createPlayer();
    //remove all the projectiles
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        free(ga_pprojectiles[i]);
        ga_pprojectiles[i] = NULL;
    }
    for (int i = 0; i < MAX_BROADCASTS; i++)
    {
        distroyBroadcast(i);
    }
    g_temp = false;
    pgame->m_numberOfProjectiles = 0;
    pgame->m_tick = 0;
    pgame->m_gameState = GAME_PLAYING;
}


Projectile_t *getProjectileByID(int ID)
{
    return ga_pprojectiles[ID];
}
Player_t *getPlayerByID(int ID)
{
    return ga_pplayers[ID];
}

void loadGameData()
{

}

void gameClose()
{
    //free game stuff
    //free players
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        free(ga_pplayers[i]);
        ga_pplayers[i] = NULL;
    }
    //free projectiles
    for(int i = 0; i < MAX_PROJECTILES; i++)
    {
        free(ga_pprojectiles[i]);
        ga_pprojectiles[i] = NULL;
    }

    //free raylib stuff
    for(int i = 0; i < TEXTURE_COUNT; i++)
        UnloadTexture(pgame->ma_textures[i]);
    CloseAudioDevice();
    CloseWindow();
}

void createBroadcast(char *text, int duration, int fontsize)
{
    t_broadcast *pbrod = malloc(sizeof(t_broadcast));
    for(int i = 0; i < MAX_BROADCASTS; i++)
    {
        if(ga_pbroadCasts[i] != NULL)continue;
        ga_pbroadCasts[i] = pbrod;
        pbrod->m_ID = i;
        break;
    }
    pbrod->m_text = text;
    pbrod->m_duration = duration;
    pbrod->m_tick = 0;
}

void broadcastTick(t_broadcast *pbrod)
{
    ++pbrod->m_tick;
    if(pbrod->m_tick >= pbrod->m_duration)
    {
        distroyBroadcast(pbrod->m_ID);
        return;
    }
}

t_broadcast *getBroadcastByID(int ID)
{
    return ga_pbroadCasts[ID];
}

void distroyBroadcast(int ID)
{
    free(ga_pbroadCasts[ID]);
    ga_pbroadCasts[ID] = NULL;
}