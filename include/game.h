#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "pipes.h"
#include "raylib.h"

#define PLAYER_SIZE 100.0f
#define SCORE_INCREMENT 4

typedef enum { GAME_RUNNING, GAME_OVER } GameStatus;

typedef struct {
  GameStatus status;
  Player player;
  Pipe pipes[MAX_PIPES];
  float score;
} GameState;

GameState InitGame();
void UpdateGame(GameState *state);
void RestartGame(GameState *state);
void DrawGame(GameState *state);

#endif
