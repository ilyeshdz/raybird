#include <raylib.h>
#include <stddef.h>

#include "game.h"

int main() {
  const int width = 1280;
  const int height = 720;

  InitWindow(width, height, "hello");
  GameState game_state = InitGame();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateGame(&game_state);
    DrawGame(&game_state);
  }

  CloseWindow();

  return 0;
}
