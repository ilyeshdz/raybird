#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <stdbool.h>

typedef struct {
  bool win;
  Player player;
} GameState;

GameState InitGame();
void UpdateGame(GameState *state);
void DrawGame(GameState *state);
#endif
