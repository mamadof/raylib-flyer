#include "helpers.h"

Color GetRandomColor()
{
  return (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(100, 255)};
}

Color GetRandomColorNoAlpha()
{
  return (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
}