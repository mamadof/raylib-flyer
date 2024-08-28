#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include <raymath.h>
#include "game.h"
#include "player.h"
#include "projectile.h"

extern game_t *pgame;
Player_t *ga_pplayers[MAX_PLAYERS];
const float g_friction = 0.95f;
const Vector2 PLAYERBODY[3] = {
-15,40,
0,0,
15,40
};
bool g_wantToShoot = false;
unsigned int g_weaponCollDown = 0;

void playerTick(Player_t *pplayer)
{
  if(pplayer->m_HP <= 0)
  {
    pgame->m_gameState = GAME_OVER;
  }
  Vector2 temp = {0};//for temperori calculations
  pgame->m_cam.target = pplayer->m_position;
  pgame->m_mousePosWorld = Vector2Add(pplayer->m_position, GetMousePosition());
  pgame->m_mousePosWorld = Vector2Subtract(pgame->m_mousePosWorld, pgame->m_cam.offset);
  //rotate points
  pplayer->m_angle = Vector2LineAngle(pplayer->m_position, pgame->m_mousePosWorld)*-1+PI/2;//idk what i did, but its working
  pplayer->m_body[0] = Vector2Rotate(PLAYERBODY[0], pplayer->m_angle);
  pplayer->m_body[1] = Vector2Rotate(PLAYERBODY[1], pplayer->m_angle);
  pplayer->m_body[2] = Vector2Rotate(PLAYERBODY[2], pplayer->m_angle);
  //rotated point + player position
  pplayer->m_body[0] = Vector2Add(pplayer->m_position, pplayer->m_body[0]);
  pplayer->m_body[1] = Vector2Add(pplayer->m_position, pplayer->m_body[1]);
  pplayer->m_body[2] = Vector2Add(pplayer->m_position, pplayer->m_body[2]);
  //calculate movments
  pplayer->m_mouserespective = Vector2Subtract(pgame->m_mousePosWorld, pplayer->m_position);
  pplayer->m_velocity = Vector2Subtract(pplayer->m_position, pplayer->m_prepos);
  pplayer->m_velocity = Vector2Add(pplayer->m_velocity, pplayer->m_prevel);
  //input
  if(IsKeyDown(KEY_SPACE))
  {
    temp = Vector2Scale(pplayer->m_mouserespective, 0.003);
    temp = Vector2ClampValue(temp, 0, 2);
    pplayer->m_velocity = Vector2Add(pplayer->m_velocity, temp);
  }
  pplayer->m_velocity = Vector2Scale(pplayer->m_velocity, g_friction);
  pplayer->m_position = Vector2Add(pplayer->m_position, pplayer->m_velocity);
  pplayer->m_prepos = pplayer->m_position;
  pplayer->m_prevel = pplayer->m_velocity;
  //handle shooting
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !g_weaponCollDown)
  {
    g_wantToShoot = true;
  }
  if(g_weaponCollDown == 0 && g_wantToShoot)
  {
    createProjectile(pplayer->m_position, pplayer->m_velocity, pplayer->m_angle);
    g_weaponCollDown = pplayer->m_weaponCoolDown;
    g_wantToShoot = false;
  }
  if(g_weaponCollDown > 0)
  {
    --g_weaponCollDown;
  }
  //movement restriction
  if(pplayer->m_position.x > GAMEWORLD_SIZE)
    pplayer->m_position.x = GAMEWORLD_SIZE;
  if(pplayer->m_position.x < -GAMEWORLD_SIZE)
    pplayer->m_position.x = -GAMEWORLD_SIZE;

  if(pplayer->m_position.y > GAMEWORLD_SIZE)
    pplayer->m_position.y = GAMEWORLD_SIZE;
  if(pplayer->m_position.y < -GAMEWORLD_SIZE)
    pplayer->m_position.y = -GAMEWORLD_SIZE;
  ++pplayer->m_tick;
}

Player_t *createPlayer()
{
  Player_t *pplayer = (Player_t*)malloc(sizeof(Player_t));
  ga_pplayers[pgame->m_numberOfPlayers] = pplayer;
  pplayer->m_position = (Vector2){0,10};
  pplayer->m_velocity = (Vector2){0,0};
  pplayer->m_prepos = (Vector2){0,0};
  pplayer->m_prevel = (Vector2){0,0};
  pplayer->m_angle = 0;
  pplayer->m_speed = 0;
  pplayer->m_body[0] = (Vector2){0,0};
  pplayer->m_body[1] = (Vector2){0,0};
  pplayer->m_body[2] = (Vector2){0,0};
  pplayer->m_color = GetRandomColor();
  pplayer->m_color.a = 255;
  pplayer->m_tick = 0;
  pplayer->m_money = 0;
  pplayer->m_maxHP = 200;
  pplayer->m_HP = pplayer->m_maxHP;
  pplayer->m_damage = 1;
  pplayer->m_weaponCoolDown = 20;
  pplayer->m_ID = pgame->m_numberOfPlayers;
  pgame->m_numberOfPlayers += 1;
  return pplayer;
}