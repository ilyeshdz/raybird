#ifndef GAME_H
#define GAME_H
#include <stdbool.h>

typedef struct {
  bool win;
} GameState;

GameState InitGame();
void UpdateGame(GameState *state);
void DrawGame(GameState *state);
#endif
