#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "pipes.h"
#include "raylib.h"

#define PLAYER_SIZE 100.0f
#define SCORE_INCREMENT 1

typedef enum { GAME_RUNNING, GAME_PAUSED, GAME_OVER } GameStatus;

typedef struct {
  GameStatus status;
  Player player;
  Pipe pipes[MAX_PIPES];
  int score;
  int highScore;
  bool shouldQuit;
} GameState;

GameState InitGame(void);
void UpdateGame(GameState *state);
void RestartGame(GameState *state);
void DrawGame(GameState *state);

#endif
