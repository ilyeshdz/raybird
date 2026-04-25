#include "game.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>

GameState InitGame() {
  const float player_size = 100.0f;
  GameState game_state = {
      .running = true,
      .score = 0,
      .player = {.position = {.y = (GetScreenHeight() - player_size) / 2.0f,
                              .x = (GetScreenWidth() - player_size) / 2.0f},
                 .size = {.x = player_size, .y = player_size},
                 .gravity = 500.0,
                 .jumpForce = 400.0,
                 .velocity = {0}}};

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

void RestartGame(GameState *state) {
  const float player_size = 100.0f;
  state->player.position = (Vector2){
      .y = (GetScreenHeight() - player_size) / 2.0f,
      .x = (GetScreenWidth() - player_size) / 2.0f,
  };
  state->score = 0;
  state->player.velocity = (Vector2){0};
  state->running = true;

  for (int i = 0; i < MAX_PIPES; i++) {
    state->pipes[i].xPos = GetScreenWidth() + (i * PIPE_SPACE);
    int minGapY = 100;
    int maxGapY = GetScreenHeight() - PIPE_WIDTH - PIPE_GAP;
    int gapCenterY = GetRandomValue(minGapY, maxGapY);

    state->pipes[i].topRect = (Rectangle){.x = state->pipes[i].xPos,
                                          .y = gapCenterY - PIPE_HEIGHT,
                                          .width = PIPE_WIDTH,
                                          .height = 600};

    state->pipes[i].bottomRect = (Rectangle){.x = state->pipes[i].xPos,
                                             .y = gapCenterY + PIPE_GAP,
                                             .width = PIPE_WIDTH,
                                             .height = PIPE_HEIGHT};
  }
}

void UpdateGame(GameState *state) {
  if (state->running) {
    state->score += 4 * GetFrameTime();
  }
  if (IsKeyPressed(KEY_SPACE) && !state->running) {
    RestartGame(state);
  };
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

    Rectangle player_rect = GetPlayerRect(&state->player);

    if (CheckCollisionRecs(state->pipes[i].topRect, player_rect) ||
        CheckCollisionRecs(state->pipes[i].bottomRect, player_rect)) {
      state->running = false;
    }
  }
}

void DrawGame(GameState *state) {
  BeginDrawing();
  Rectangle player = GetPlayerRect(&state->player);
  ClearBackground(BLACK);
  DrawText(TextFormat("Score: %d", (int)state->score), 25, 25, 20, WHITE);
  if (!state->running) {
    DrawText("FINISH", (GetScreenWidth() - MeasureText("FINISH", 20)) / 2.0f,
             (GetScreenHeight() - 20) / 2.0f, 20, RED);
  } else {
    for (int i = 0; i < MAX_PIPES; i++) {
      DrawRectangleRec(state->pipes[i].bottomRect, BLUE);
      DrawRectangleRec(state->pipes[i].topRect, BLUE);
    }
    DrawRectangleRec(player, LIGHTGRAY);
  }
  EndDrawing();
}
