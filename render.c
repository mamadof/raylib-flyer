#include <raylib.h>
#include <stdio.h>
#include <raymath.h>
#include "render.h"
#include "helpers.h"
#include "player.h"
#include "game.h"
#include "enemy.h"
#include "world_interface.h"
extern game_t *pgame;

static char g_text[600];

void renderAll()
{
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    BeginMode2D(pgame->m_cam);

    sprintf(g_text, "fps: %d\n\n"
    "Enemies: %lu\n\n"
    "use q to quit\n\n"
    "use r to reset\n\n"
    "use lmb to shoot and choose\n\n"
    "use space to accelerate", 
    GetFPS(),
    pgame->m_numberOfEnemys);
    DrawText(g_text, -100, -100, 20, BLACK);
    // Image block = LoadImage("data/images/block.png");
    // Texture2D texture = LoadTextureFromImage(block);
    // Texture2D texture = LoadTexture("data/images/block.png");
    drawGrid();
    drawGameBoarder();

    //render players
    if(pgame->m_numberOfPlayers > 0)
    {
        for(int i=0; i< pgame->m_numberOfPlayers; i++)//render players
        {
            Player_t *pplayer = getPlayerByID(i);
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
    if(pgame->m_numberOfProjectiles > 0)
    {
        for(int i=0; i< MAX_PROJECTILES; i++)//render players
        {
            Projectile_t *pprojec = getProjectileByID(i);
            if(pprojec == NULL)continue;
            DrawCircleV(pprojec->m_position, pprojec->m_radios, pprojec->m_color);
        }
    }
    //render enemies
    if(pgame->m_numberOfEnemys > 0)
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

void drawGrid()
{
    int distance;
    for(int x = -GAMEWORLD_SIZE/50; x < GAMEWORLD_SIZE/50; x++)
    {
        for(int y = -GAMEWORLD_SIZE/50; y < GAMEWORLD_SIZE/50; y++)
        {
            distance = Vector2Distance((Vector2){x,y}, (Vector2){0,0});
            DrawTexture(pgame->ma_textures[TEXTURE_BLOCK],
            pgame->ma_textures[TEXTURE_BLOCK].width*x,
            pgame->ma_textures[TEXTURE_BLOCK].height*y,
            (Color){distance*2,distance*2,0,distance*2});
        }
    }
}

void drawGameBoarder()
{
    int textureWidth = pgame->ma_textures[TEXTURE_BOARDER].width;
    int textureheight = pgame->ma_textures[TEXTURE_BOARDER].height;
    int xiter = GAMEWORLD_SIZE/textureWidth;
    int yiter = GAMEWORLD_SIZE/textureheight;
    for(int x = 0; x <= yiter; x++)
    {
        for(int y = 0; y <= yiter; y++)
        {
            //draw boarder up and down
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], x*textureWidth, -GAMEWORLD_SIZE-textureheight, RED);
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], -x*textureWidth, -GAMEWORLD_SIZE-textureheight, RED);
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], x*textureWidth, GAMEWORLD_SIZE, RED);
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], -x*textureWidth, GAMEWORLD_SIZE, RED);
            //draw boarder left and right
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], -GAMEWORLD_SIZE-textureWidth, y*textureheight, RED);
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], -GAMEWORLD_SIZE-textureWidth, -y*textureheight-textureheight, RED);
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], GAMEWORLD_SIZE, y*textureheight, RED);
            DrawTexture(pgame->ma_textures[TEXTURE_BOARDER], GAMEWORLD_SIZE, -y*textureheight, RED);
        }
    }

}