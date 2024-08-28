#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <raylib.h>

typedef struct {
  Vector2 m_position;
  Vector2 m_velocity;
  float m_radios;
  float m_speed;
  float m_angle;
  Color m_color;
  int m_damage;
  bool m_homing;
  unsigned long m_tick;
  int m_ID;
}Projectile_t;

Projectile_t *createProjectile(Vector2 pos, Vector2 vel, float angle);
void projectileTick(Projectile_t *pprojec);
void distroyProjectile(int ID);

#endif //PROJECTILE_H