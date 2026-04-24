#include <raylib.h>

int main() {
  const int width = 1280;
  const int height = 720;

  InitWindow(width, height, "hello");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GRAY);
    DrawText("hello", 190, 200, 20, WHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
