#include "game.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>

void InitPipe(Pipe *pipe, float xPos) {
  pipe->xPos = xPos;
  int minGapY = MIN_GAP_Y;
  int maxGapY = GetScreenHeight() - PIPE_WIDTH - PIPE_GAP;
  int gapCenterY = GetRandomValue(minGapY, maxGapY);

  pipe->topRect = (Rectangle){.x = xPos,
                               .y = gapCenterY - PIPE_HEIGHT,
                               .width = PIPE_WIDTH,
                               .height = PIPE_HEIGHT};

  pipe->bottomRect = (Rectangle){.x = xPos,
                                  .y = gapCenterY + PIPE_GAP,
                                  .width = PIPE_WIDTH,
                                  .height = PIPE_HEIGHT};
}

GameState InitGame() {
  GameState game_state = {
      .status = GAME_RUNNING,
      .score = 0,
      .player = {.position = {.y = (GetScreenHeight() - PLAYER_SIZE) / 2.0f,
                              .x = (GetScreenWidth() - PLAYER_SIZE) / 2.0f},
                 .size = {.x = PLAYER_SIZE, .y = PLAYER_SIZE},
                 .gravity = 500.0,
                 .jumpForce = 400.0,
                 .velocity = {0}}};

  for (int i = 0; i < MAX_PIPES; i++) {
    InitPipe(&game_state.pipes[i], GetScreenWidth() + (i * PIPE_SPACE));
  }

  return game_state;
}

void RestartGame(GameState *state) {
  state->player.position = (Vector2){
      .y = (GetScreenHeight() - PLAYER_SIZE) / 2.0f,
      .x = (GetScreenWidth() - PLAYER_SIZE) / 2.0f,
  };
  state->score = 0;
  state->player.velocity = (Vector2){0};
  state->status = GAME_RUNNING;

  for (int i = 0; i < MAX_PIPES; i++) {
    InitPipe(&state->pipes[i], GetScreenWidth() + (i * PIPE_SPACE));
  }
}

void UpdateGame(GameState *state) {
  if (state->status == GAME_RUNNING) {
    state->score += SCORE_INCREMENT * GetFrameTime();
  }
  if (IsKeyPressed(KEY_SPACE) && state->status == GAME_OVER) {
    RestartGame(state);
  };
  if (IsKeyPressed(KEY_SPACE)) {
    PlayerJump(&state->player);
  }
  UpdatePlayer(&state->player);
  for (int i = 0; i < MAX_PIPES; i++) {
    state->pipes[i].bottomRect.x -= PIPE_SPEED * GetFrameTime();
    state->pipes[i].topRect.x -= PIPE_SPEED * GetFrameTime();

    if (state->pipes[i].topRect.x + PIPE_WIDTH < 0) {
      InitPipe(&state->pipes[i], state->pipes[i].topRect.x + (MAX_PIPES * PIPE_SPACE));
    }

    Rectangle player_rect = GetPlayerRect(&state->player);

    if (CheckCollisionRecs(state->pipes[i].topRect, player_rect) ||
        CheckCollisionRecs(state->pipes[i].bottomRect, player_rect)) {
      state->status = GAME_OVER;
    }
  }
}

void DrawGame(GameState *state) {
  BeginDrawing();
  Rectangle player = GetPlayerRect(&state->player);
  ClearBackground(BLACK);
  DrawText(TextFormat("Score: %d", (int)state->score), 25, 25, 20, WHITE);
  if (state->status == GAME_OVER) {
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
