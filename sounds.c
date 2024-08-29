#include "sounds.h"
#include <raylib.h>
#include "player.h"
#include <raymath.h>

Sound ga_sounds[SOUND_COUNT];
const unsigned int g_howFarCanYouHear = 1300;
const float g_soundOffset = 0.4;

void playGameSound(GameSounds sound, Vector2 pos, SoundMask SoundMask)
{
    if(SoundMask == MASK_GLOBAL)
    {
        PlaySound(ga_sounds[sound]);
    }else if(SoundMask == MASK_DISTANT){
        unsigned int distance = Vector2Distance(pos, getPlayerByID(0)->m_position);
        if(distance > g_howFarCanYouHear)return;
        SetSoundVolume(ga_sounds[sound], ((g_howFarCanYouHear-distance)*((float)1/g_howFarCanYouHear))-g_soundOffset);
        PlaySound(ga_sounds[sound]);
    }
}

void loadGameSounds()
{
    ga_sounds[SOUND_SHOOT] = LoadSound("data/sounds/shoot.mp3");
    SetSoundPitch(ga_sounds[SOUND_SHOOT], 2);
    SetSoundVolume(ga_sounds[SOUND_SHOOT], 0.3);

    ga_sounds[SOUND_ENEMY_DIE] = LoadSound("data/sounds/enemy_dies.mp3");
}