#include <raylib.h>
#include <stdio.h>
#include <raymath.h>
#include "render.h"
#include "helpers.h"
#include "player.h"
#include "game.h"
#include "enemy.h"
#include "world_interface.h"
#include "texture.h"
extern game_t *pgame;

static char g_text[600];

void renderAll()
{
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    BeginMode2D(pgame->m_cam);
    //draw the world
    DrawTexture(getWorldTexture().texture, -GAMEWORLD_SIZE, -GAMEWORLD_SIZE, WHITE);

    sprintf(g_text, "fps: %d\n\n"
    "Enemies: %lu\n\n"
    "use q to quit\n\n"
    "use r to reset\n\n"
    "use lmb to shoot and choose\n\n"
    "use space to accelerate", 
    GetFPS(),
    getNumberOfEnemies());
    DrawText(g_text, -100, -100, 20, BLACK);
    //render players
    if(getNumberOfPlayers() > 0)
    {
        for(int i=0; i < MAX_PLAYERS; i++)//render players
        {
            Player_t *pplayer = getPlayerByID(i);
            if(pplayer == NULL)continue;
            DrawTriangle(
            pplayer->m_body[1],
            pplayer->m_body[0],
            pplayer->m_body[2],
            pplayer->m_color);
        }
        //draw player's stats
        EndMode2D();
        sprintf(g_text, "%lld", getPlayerByID(0)->m_money);
        DrawText(g_text, 10, 30, 40, BLACK);
        //render player's hp
        DrawRectangle(10, 10,//maxhp
        getPlayerByID(0)->m_maxHP, 20, BLACK);
        DrawRectangle(15, 15,
        getPlayerByID(0)->m_HP-10, 10, RED);
        BeginMode2D(pgame->m_cam);
    }
    //render projectiles
    if(getNumberOfProjectiles() > 0)
    {
        for(int i=0; i< MAX_PROJECTILES; i++)//render players
        {
            Projectile_t *pprojec = getProjectileByID(i);
            if(pprojec == NULL)continue;
            DrawCircleV(pprojec->m_position, pprojec->m_radios, pprojec->m_color);
        }
    }
    //render enemies
    if(getNumberOfEnemies() > 0)
    {
        for(int i=0; i< MAX_ENEMIES; i++)
        {
            enemy_t *penemy = getEnemyByID(i);
            if(penemy == NULL)continue;
            DrawCircleV(penemy->m_position, penemy->m_radios, penemy->m_color);
            //draw theyr hp
            DrawRectangle(penemy->m_position.x - penemy->m_radios/2,
            penemy->m_position.y+penemy->m_radios+5,
            penemy->m_radios - (penemy->m_maxHP-penemy->m_HP),//width
            penemy->m_radios/10,//height
            BLACK);
        }
    }


    for (int i = 0; i < TEXT_COUNT; i++)
    {
        textBox_t *ptext = getTextBoxByID(i);
        if(ptext == NULL || !ptext->m_show) continue;
        DrawText(ptext->m_text, ptext->m_pos.x, ptext->m_pos.y, ptext->m_fontsize, ptext->m_color);
    }

    //broadcasts
    for(int i = 0; i < MAX_BROADCASTS; i++)
    {
        t_broadcast *pbrod;
        pbrod = getBroadcastByID(i);
        if(pbrod == NULL)continue;
        EndMode2D();
        DrawText(pbrod->m_text, (GetScreenWidth()/2)-100, GetScreenHeight()/2, 50, BLACK);
        BeginMode2D(pgame->m_cam);
    }
    EndMode2D();
    EndDrawing();
}