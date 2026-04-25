#include "game.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>

GameState InitGame() {
  const float player_size = 100.0f;
  GameState game_state = {
      .win = false,
      .player = {.position = {.y = (GetScreenHeight() - player_size) / 2.0f,
                              .x = (GetScreenWidth() - player_size) / 2.0f},
                 .size = {.x = player_size, .y = player_size},
                 .gravity = 500.0,
                 .jumpForce = 400.0,
                 .velocity = {.x = 0, .y = 0}}};

  for (int i = 0; i < MAX_PIPES; i++) {
    game_state.pipes[i].xPos = GetScreenWidth() + (i * PIPE_SPACE);
    int minGapY = 100;
    int maxGapY = GetScreenHeight() - PIPE_WIDTH - PIPE_GAP;
    int gapCenterY = GetRandomValue(minGapY, maxGapY);

    game_state.pipes[i].topRect = (Rectangle){.x = game_state.pipes[i].xPos,
                                              .y = gapCenterY - PIPE_HEIGHT,
                                              .width = PIPE_WIDTH,
                                              .height = 600};

    game_state.pipes[i].bottomRect = (Rectangle){.x = game_state.pipes[i].xPos,
                                                 .y = gapCenterY + PIPE_GAP,
                                                 .width = PIPE_WIDTH,
                                                 .height = PIPE_HEIGHT};
  }

  return game_state;
}
void UpdateGame(GameState *state) {
  if (IsKeyPressed(KEY_SPACE)) {
    PlayerJump(&state->player);
  }
  UpdatePlayer(&state->player);
  for (int i = 0; i < MAX_PIPES; i++) {
    state->pipes[i].bottomRect.x -= 200 * GetFrameTime();
    state->pipes[i].topRect.x -= 200 * GetFrameTime();

    if (state->pipes[i].topRect.x + PIPE_WIDTH < 0) {
      state->pipes[i].topRect.x += (MAX_PIPES * PIPE_SPACE);
      state->pipes[i].bottomRect.x += (MAX_PIPES * PIPE_SPACE);

      int minGapY = 100;
      int maxGapY = GetScreenHeight() - (PIPE_WIDTH + 50) - PIPE_GAP;
      int gapCenterY = GetRandomValue(minGapY, maxGapY);

      state->pipes[i].bottomRect.y =
          gapCenterY - state->pipes[i].topRect.height;
      state->pipes[i].bottomRect.y = gapCenterY + PIPE_GAP;
    }
  }
}
void DrawGame(GameState *state) {
  BeginDrawing();
  Rectangle player = GetPlayerRect(&state->player);
  ClearBackground(BLACK);
  for (int i = 0; i < MAX_PIPES; i++) {
    DrawRectangleRec(state->pipes[i].bottomRect, BLUE);
    DrawRectangleRec(state->pipes[i].topRect, BLUE);
  }
  DrawRectangleRec(player, LIGHTGRAY);
  EndDrawing();
}
