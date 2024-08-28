#ifndef  SOUNDS_H
#define SOUNDS_H
#include <raylib.h>

typedef enum {
  SOUND_SHOOT,
  SOUND_SHOOT_2,
  SOUND_HURT,
  SOUND_HIT,
  SOUND_ENEMY_DIE,
  SOUND_GAMEOVER,
  SOUND_BUY,
  SOUND_HOVER,
  SOUND_COUNT
}GameSounds;

typedef enum{
  MASK_GLOBAL,
  MASK_DISTANT,
  MASK_COUNT
}SoundMask;

void loadGameSounds();
void playGameSound(GameSounds, Vector2 pos, SoundMask);

#endif //SOUNDS_H