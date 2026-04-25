#include "game.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>

GameState InitGame() {
  return (GameState){.win = false,
                     .player = {.position = {.y = 0, .x = 0},
                                .size = {.x = 100, .y = 100},
                                .gravity = 500.0,
                                .jumpForce = 400.0,
                                .velocity = {.x = 0, .y = 0}}};
}
void UpdateGame(GameState *state) {
  if (IsKeyPressed(KEY_SPACE)) {
    state->player.velocity.y = -state->player.jumpForce;
  }
  state->player.velocity.y += state->player.gravity * GetFrameTime();
  state->player.position.y += state->player.velocity.y * GetFrameTime();
}
void DrawGame(GameState *state) {
  BeginDrawing();
  Rectangle player = GetPlayerRect(&state->player);
  DrawRectangleRec(player, LIGHTGRAY);
  ClearBackground(BLACK);
  EndDrawing();
}
