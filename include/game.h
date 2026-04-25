#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "raylib.h"
#include <stdbool.h>

#define PIPE_GAP 300
#define MAX_PIPES 5
#define PIPE_WIDTH 100
#define PIPE_HEIGHT 600
#define PIPE_SPACE 400

typedef struct {
  Rectangle topRect;
  Rectangle bottomRect;
  float xPos;
} Pipe;

typedef struct {
  bool running;
  Player player;
  Pipe pipes[MAX_PIPES];
} GameState;

GameState InitGame();
void UpdateGame(GameState *state);
void RestartGame(GameState *state);
void DrawGame(GameState *state);
#endif
