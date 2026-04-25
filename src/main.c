#include <raylib.h>
#include <stddef.h>

#include "game.h"

int main(void) {
  const int width = 1280;
  const int height = 720;

  InitWindow(width, height, "hello");
  SetExitKey(0); // Disable ESC key closing the window
  GameState game_state = InitGame();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateGame(&game_state);
    if (game_state.shouldQuit) break;
    DrawGame(&game_state);
  }

  CloseWindow();

  return 0;
}
