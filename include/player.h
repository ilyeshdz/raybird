#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define PLAYER_GRAVITY 500.0f
#define PLAYER_JUMP_FORCE 400.0f

typedef struct {
  Vector2 position;
  Vector2 velocity;
  Vector2 size;

  float gravity;
  float jumpForce;
} Player;

Rectangle GetPlayerRect(const Player *p);
void UpdatePlayer(Player *p);
void PlayerJump(Player *p);

#endif
