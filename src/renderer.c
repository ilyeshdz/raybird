#include "renderer.h"
#include "player.h"
#include "pipes.h"
#include "raylib.h"

void RenderPlayer(const Player *player) {
  Rectangle player_rect = GetPlayerRect(player);
  DrawRectangleRec(player_rect, LIGHTGRAY);
}

void RenderPipes(const Pipe *pipes, int count) {
  for (int i = 0; i < count; i++) {
    DrawRectangleRec(pipes[i].bottomRect, BLUE);
    DrawRectangleRec(pipes[i].topRect, BLUE);
  }
}

void RenderPauseMenu(const GameState *state) {
  (void)state; // Unused parameter
  
  const char *title = "PAUSED";
  const char *resume = "[ESC] Resume";
  const char *restart = "[R] Restart";
  const char *quit = "[Q] Quit";
  
  int titleSize = 40;
  int menuSize = 20;
  
  DrawText(title, (GetScreenWidth() - MeasureText(title, titleSize)) / 2.0f,
           GetScreenHeight() / 4.0f, titleSize, YELLOW);
  DrawText(resume, (GetScreenWidth() - MeasureText(resume, menuSize)) / 2.0f,
           GetScreenHeight() / 2.0f, menuSize, WHITE);
  DrawText(restart, (GetScreenWidth() - MeasureText(restart, menuSize)) / 2.0f,
           GetScreenHeight() / 2.0f + 30, menuSize, WHITE);
  DrawText(quit, (GetScreenWidth() - MeasureText(quit, menuSize)) / 2.0f,
           GetScreenHeight() / 2.0f + 60, menuSize, WHITE);
}

void RenderUI(const GameState *state) {
  DrawText(TextFormat("Score: %d", (int)state->score), 25, 25, 20, WHITE);
  
  if (state->status == GAME_OVER) {
    DrawText("FINISH", (GetScreenWidth() - MeasureText("FINISH", 20)) / 2.0f,
             (GetScreenHeight() - 20) / 2.0f, 20, RED);
  } else if (state->status == GAME_PAUSED) {
    RenderPauseMenu(state);
  }
}

void RenderGame(const GameState *state) {
  BeginDrawing();
  ClearBackground(BLACK);
  
  if (state->status == GAME_RUNNING || state->status == GAME_PAUSED) {
    RenderPipes(state->pipes, MAX_PIPES);
    RenderPlayer(&state->player);
  }
  
  RenderUI(state);
  EndDrawing();
}
