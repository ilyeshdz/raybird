#include "player.h"
#include "raylib.h"

Rectangle GetPlayerRect(const Player *p) {
  return (Rectangle){.x = p->position.x,
                     .y = p->position.y,
                     .height = p->size.y,
                     .width = p->size.x};
}

void PlayerJump(Player *p) { p->velocity.y = -p->jumpForce; }

void UpdatePlayer(Player *p) {
  p->velocity.y += p->gravity * GetFrameTime();
  p->position.y += p->velocity.y * GetFrameTime();
}
