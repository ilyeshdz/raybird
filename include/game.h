#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "raylib.h"

#define PIPE_GAP 300
#define MAX_PIPES 5
#define PIPE_WIDTH 100
#define PIPE_HEIGHT 600
#define PIPE_SPACE 400
#define PLAYER_SIZE 100.0f
#define PIPE_SPEED 200.0f
#define SCORE_INCREMENT 4
#define MIN_GAP_Y 100

typedef enum { GAME_RUNNING, GAME_OVER } GameStatus;

typedef struct {
  Rectangle topRect;
  Rectangle bottomRect;
  float xPos;
} Pipe;

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
