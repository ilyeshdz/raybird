#include "renderer.h"
#include "player.h"
#include "pipes.h"
#include "raylib.h"

void RenderPlayer(const Player *player) {
  Rectangle player_rect = GetPlayerRect((Player *)player);
  DrawRectangleRec(player_rect, LIGHTGRAY);
}

void RenderPipes(const Pipe *pipes, int count) {
  for (int i = 0; i < count; i++) {
    DrawRectangleRec(pipes[i].bottomRect, BLUE);
    DrawRectangleRec(pipes[i].topRect, BLUE);
  }
}

void RenderUI(const GameState *state) {
  DrawText(TextFormat("Score: %d", (int)state->score), 25, 25, 20, WHITE);
  
  if (state->status == GAME_OVER) {
    DrawText("FINISH", (GetScreenWidth() - MeasureText("FINISH", 20)) / 2.0f,
             (GetScreenHeight() - 20) / 2.0f, 20, RED);
  }
}

void RenderGame(const GameState *state) {
  BeginDrawing();
  ClearBackground(BLACK);
  
  if (state->status == GAME_RUNNING) {
    RenderPipes(state->pipes, MAX_PIPES);
    RenderPlayer(&state->player);
  }
  
  RenderUI(state);
  EndDrawing();
}
