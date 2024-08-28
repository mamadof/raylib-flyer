#ifndef SPACE_ROCK_H
#define SPACE_ROCK_H
#include <raylib.h>

typedef struct {
  Vector2 m_position;
  Vector2 m_velocity;
  float m_radios;
  float m_speed;
  Color m_color;
  long int m_maxHP;
  long int m_HP;
  float m_damage;
  float m_initialSpeed;
  unsigned long m_tick;
  int m_ID;
}enemy_t;
enemy_t *createEnemy(Vector2 pos, Vector2 vel);
void EnemyTick(enemy_t *penemy);
enemy_t *getEnemyByID(int ID);
void distroyEnemy(int ID);
unsigned long getNumberOfEnemies();

#endif //SPACE_ROCK_H