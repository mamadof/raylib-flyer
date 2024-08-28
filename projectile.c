#include "projectile.h"
#include <raylib.h>
#include "game.h"
#include <stdlib.h>
#include <raymath.h>
#include "helpers.h"
#include "enemy.h"

extern game_t *pgame;
Projectile_t *ga_pprojectiles[MAX_PROJECTILES];

void projectileTick(Projectile_t *pprojec)
{
  //projectile lifespan
  if (pprojec->m_tick > 200)
  {
    distroyProjectile(pprojec->m_ID);
    return;
  }
  //movement restriction
  if(pprojec->m_position.x > GAMEWORLD_SIZE)
  {
    distroyProjectile(pprojec->m_ID);
    return;
  }
  if(pprojec->m_position.x < -GAMEWORLD_SIZE)
  {
    distroyProjectile(pprojec->m_ID);
    return;
  }

  if(pprojec->m_position.y > GAMEWORLD_SIZE)
  {
    distroyProjectile(pprojec->m_ID);
    return;
  }
  if(pprojec->m_position.y < -GAMEWORLD_SIZE)
  {
    distroyProjectile(pprojec->m_ID);
    return;
  }
  //check collition againt everything o_0
  for(int i = 0; i < MAX_ENEMIES; i++)
  {
    if(getEnemyByID(i) == NULL)continue;
    if(CheckCollisionCircles(pprojec->m_position, pprojec->m_radios, getEnemyByID(i)->m_position, getEnemyByID(i)->m_radios))
    {
      getEnemyByID(i)->m_HP -= pprojec->m_damage;
      distroyProjectile(pprojec->m_ID);
      return;
    }
  }

  pprojec->m_position = Vector2Add(pprojec->m_position, pprojec->m_velocity);
  ++pprojec->m_tick;
}

Projectile_t *createProjectile(Vector2 pos, Vector2 vel, float angle)
{
  Projectile_t *pprojec = malloc(sizeof(Projectile_t));
  for(unsigned long i = 0; i < MAX_PROJECTILES; i++)
  {
    if(ga_pprojectiles[i] != NULL)continue;
    ga_pprojectiles[i] = pprojec;
    pprojec->m_ID = i;
    break;
  }

  Vector2 projSpeed = Vector2Rotate((Vector2){0,-10}, angle);
  // projvel = Vector2Add(projvel, vel);
  // pprojec->m_velocity = Vector2Add(projSpeed, Vector2Scale(vel, 0.5f));
  pprojec->m_velocity = projSpeed;
  pprojec->m_position = pos;
  pprojec->m_color = GetRandomColorNoAlpha();
  pprojec->m_radios = GetRandomValue(5, 10);
  pprojec->m_damage = pprojec->m_radios*2;
  pprojec->m_tick = 0;

  ++pgame->m_numberOfProjectiles;
  return pprojec;
}

void distroyProjectile(int ID)
{
  free(ga_pprojectiles[ID]);
  ga_pprojectiles[ID] = NULL;
  --pgame->m_numberOfProjectiles;
}
