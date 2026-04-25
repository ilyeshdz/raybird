#ifndef PIPES_H
#define PIPES_H

#include "raylib.h"

#define BASE_PIPE_GAP 300
#define MAX_PIPES 5
#define PIPE_WIDTH 100
#define PIPE_HEIGHT 600
#define PIPE_SPACE 400
#define BASE_PIPE_SPEED 200.0f
#define MIN_GAP_Y 100
#define MIN_PIPE_GAP 180
#define SPEED_INCREMENT_PER_SCORE 5.0f
#define GAP_DECREMENT_PER_SCORE 2

typedef struct {
  Rectangle topRect;
  Rectangle bottomRect;
  float xPos;
  bool passed;
} Pipe;

void InitPipe(Pipe *pipe, float xPos, int score);
void UpdatePipes(Pipe *pipes, int count, int score);
void ResetPipes(Pipe *pipes, int count, int score);

#endif
