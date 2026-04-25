#include "player.h"
#include "raylib.h"

Rectangle GetPlayerRect(Player *p) {
  return (Rectangle){.x = p->position.x,
                     .y = p->position.y,
                     .height = p->size.y,
                     .width = p->size.x};
};
