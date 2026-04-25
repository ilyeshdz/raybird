#ifndef PIPES_H
#define PIPES_H

#include "raylib.h"

#define PIPE_GAP 300
#define MAX_PIPES 5
#define PIPE_WIDTH 100
#define PIPE_HEIGHT 600
#define PIPE_SPACE 400
#define PIPE_SPEED 200.0f
#define MIN_GAP_Y 100

typedef struct {
  Rectangle topRect;
  Rectangle bottomRect;
  float xPos;
} Pipe;

void InitPipe(Pipe *pipe, float xPos);
void UpdatePipes(Pipe *pipes, int count);
void ResetPipes(Pipe *pipes, int count);

#endif
