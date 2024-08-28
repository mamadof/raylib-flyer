#include <stdlib.h>
#include "enemy.h"
#include "game.h"
#include <stdlib.h>
#include "helpers.h"
#include <raymath.h>
#include <math.h>

enemy_t *ga_pEnemys[MAX_ENEMIES];
extern game_t *pgame;

enemy_t *createEnemy(Vector2 pos, Vector2 vel)
{
    enemy_t *penemy = malloc(sizeof(enemy_t));
    int i = 0;
    for(; i < MAX_ENEMIES; i++)
    {
        if (ga_pEnemys[i] != NULL)continue;
        ga_pEnemys[i] = penemy;
        break;
    }
    penemy->m_position = pos;
    penemy->m_velocity = vel;
    penemy->m_radios = GetRandomValue(20, 60);
    penemy->m_color = GetRandomColor();
    penemy->m_tick = 0;
    penemy->m_initialSpeed = GetRandomValue(1, 3+pgame->m_wave);
    penemy->m_maxHP = penemy->m_radios;
    penemy->m_HP = penemy->m_maxHP;
    penemy->m_ID = i;
    ++pgame->m_numberOfEnemys;
    return penemy;
}

enemy_t *getEnemyByID(int ID)
{
    return ga_pEnemys[ID];
}

void EnemyTick(enemy_t *penemy)
{
    //die from projectile
    if(penemy->m_HP <= 0)
    {
        getPlayerByID(0)->m_money += roundf(penemy->m_radios/5) * (pgame->m_wave+1);
        distroyEnemy(penemy->m_ID);
        return;
    }
    penemy->m_position = Vector2MoveTowards(penemy->m_position, getPlayerByID(0)->m_position, penemy->m_initialSpeed);
    ++penemy->m_tick;
}

void distroyEnemy(int ID)
{
    free(ga_pEnemys[ID]);
    ga_pEnemys[ID] = NULL;
    --pgame->m_numberOfEnemys;
}
