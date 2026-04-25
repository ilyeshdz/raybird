#include "renderer.h"
#include "player.h"
#include "pipes.h"
#include "particles.h"
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

void RenderPauseMenu(void) {
  const char *title = "PAUSED";
  const char *resume = "[ESC] Resume";
  const char *restart = "[R] Restart";
  const char *quit = "[Q] Quit";
  
  DrawText(title, (GetScreenWidth() - MeasureText(title, PAUSE_TITLE_SIZE)) / 2.0f,
           GetScreenHeight() / 4.0f, PAUSE_TITLE_SIZE, YELLOW);
  DrawText(resume, (GetScreenWidth() - MeasureText(resume, PAUSE_MENU_SIZE)) / 2.0f,
           GetScreenHeight() / 2.0f, PAUSE_MENU_SIZE, WHITE);
  DrawText(restart, (GetScreenWidth() - MeasureText(restart, PAUSE_MENU_SIZE)) / 2.0f,
           GetScreenHeight() / 2.0f + PAUSE_MENU_SPACING, PAUSE_MENU_SIZE, WHITE);
  DrawText(quit, (GetScreenWidth() - MeasureText(quit, PAUSE_MENU_SIZE)) / 2.0f,
           GetScreenHeight() / 2.0f + (PAUSE_MENU_SPACING * 2), PAUSE_MENU_SIZE, WHITE);
}

void RenderUI(const GameState *state) {
  DrawText(TextFormat("Score: %d", state->score), UI_SCORE_X, UI_SCORE_Y, UI_FONT_SIZE, WHITE);
  DrawText(TextFormat("Best: %d", state->highScore), UI_SCORE_X, UI_SCORE_Y + 30, UI_FONT_SIZE, YELLOW);

  if (state->debugMode) {
    DrawText("[DEBUG MODE]", UI_SCORE_X, UI_SCORE_Y + 60, UI_FONT_SIZE, GREEN);
    DrawText("[1]+5 [2]+10 [3]+25 [0]Reset", UI_SCORE_X, UI_SCORE_Y + 90, UI_FONT_SIZE, GREEN);
  }

#ifdef DEBUG
  DrawText(TextFormat("FPS: %d", GetFPS()), UI_SCORE_X, UI_SCORE_Y + 120, UI_FONT_SIZE, GREEN);
#endif

  if (state->status == GAME_OVER) {
    DrawText("FINISH", (GetScreenWidth() - MeasureText("FINISH", UI_FONT_SIZE)) / 2.0f,
             (GetScreenHeight() - UI_FONT_SIZE) / 2.0f, UI_FONT_SIZE, RED);
  } else if (state->status == GAME_PAUSED) {
    RenderPauseMenu();
  }
}

void RenderGame(const GameState *state) {
  BeginDrawing();
  ClearBackground(BLACK);
  
  if (state->status == GAME_RUNNING || state->status == GAME_PAUSED) {
    RenderPipes(state->pipes, MAX_PIPES);
    RenderPlayer(&state->player);
  }
  
  RenderParticles(&state->particles);
  RenderUI(state);
  EndDrawing();
}
