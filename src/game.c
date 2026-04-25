#include "game.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>

GameState InitGame() {
  const float player_size = 100.0f;
  return (GameState){
      .win = false,
      .player = {.position = {.y = (GetScreenHeight() - player_size) / 2.0f,
                              .x = (GetScreenWidth() - player_size) / 2.0f},
                 .size = {.x = player_size, .y = player_size},
                 .gravity = 500.0,
                 .jumpForce = 400.0,
                 .velocity = {.x = 0, .y = 0}}};
}
void UpdateGame(GameState *state) {
  if (IsKeyPressed(KEY_SPACE)) {
    PlayerJump(&state->player);
  }
  UpdatePlayer(&state->player);
}
void DrawGame(GameState *state) {
  BeginDrawing();
  Rectangle player = GetPlayerRect(&state->player);
  DrawRectangleRec(player, LIGHTGRAY);
  ClearBackground(BLACK);
  EndDrawing();
}
