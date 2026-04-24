#include <raylib.h>
#include <stddef.h>

#include "game.h"

int main() {
  const int width = 1280;
  const int height = 720;

  GameState game_state = InitGame();
  InitWindow(width, height, "hello");

  while (!WindowShouldClose()) {
    UpdateGame(&game_state);
    DrawGame(&game_state);
  }

  CloseWindow();

  return 0;
}
