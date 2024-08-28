#include <raylib.h>
#include <stdio.h>
#include "game.h"

extern game_t *pgame;

int main(int argc, char *argv[])
{
  gameInit();
  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q))
  {
    gameTick();
  }
  CloseWindow();
  return 0;
}