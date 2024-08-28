#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>


typedef struct {
  Vector2 m_position;
  Vector2 m_prepos;
  Vector2 m_velocity;
  Vector2 m_prevel;
  Vector2 m_mouserespective;//mouse position respective to the player
  Vector2 m_body[3];
  float m_speed;
  float m_angle;
  Color m_color;
  long int m_maxHP;
  long int m_HP;
  long int m_damage;
  unsigned int m_weaponCoolDown;
  unsigned long long m_money;
  unsigned long m_tick;
  int m_ID;
}Player_t;

void playerTick(Player_t *pplayer);
Player_t *createPlayer();


#endif //PLAYER_H