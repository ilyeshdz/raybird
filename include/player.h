#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
  Vector2 position;
  Vector2 velocity;
  Vector2 size;

  float gravity;
  float jumpForce;
} Player;

Rectangle GetPlayerRect(Player *p);
void UpdatePlayer(Player *p);
void PlayerJump(Player *p);

#endif
