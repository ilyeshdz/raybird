#include "pipes.h"
#include "raylib.h"

static float GetCurrentPipeGap(int score) {
  float gap = BASE_PIPE_GAP - (score * GAP_DECREMENT_PER_SCORE);
  if (gap < MIN_PIPE_GAP) gap = MIN_PIPE_GAP;
  return gap;
}

static float GetCurrentPipeSpeed(int score) {
  return BASE_PIPE_SPEED + (score * SPEED_INCREMENT_PER_SCORE);
}

void InitPipe(Pipe *pipe, float xPos, int score) {
  pipe->xPos = xPos;
  pipe->passed = false;
  float currentGap = GetCurrentPipeGap(score);
  int maxGapY = GetScreenHeight() - PIPE_WIDTH - currentGap;
  int gapCenterY = GetRandomValue(MIN_GAP_Y, maxGapY);

  pipe->topRect = (Rectangle){.x = xPos,
                               .y = gapCenterY - PIPE_HEIGHT,
                               .width = PIPE_WIDTH,
                               .height = PIPE_HEIGHT};

  pipe->bottomRect = (Rectangle){.x = xPos,
                                  .y = gapCenterY + currentGap,
                                  .width = PIPE_WIDTH,
                                  .height = PIPE_HEIGHT};
}

void UpdatePipes(Pipe *pipes, int count, int score) {
  float currentSpeed = GetCurrentPipeSpeed(score);
  for (int i = 0; i < count; i++) {
    pipes[i].bottomRect.x -= currentSpeed * GetFrameTime();
    pipes[i].topRect.x -= currentSpeed * GetFrameTime();

    if (pipes[i].topRect.x + PIPE_WIDTH < 0) {
      // Find the rightmost pipe
      float maxRight = 0.0f;
      for (int j = 0; j < count; j++) {
        if (pipes[j].topRect.x > maxRight) {
          maxRight = pipes[j].topRect.x;
        }
      }
      // Place the recycled pipe immediately after the rightmost pipe
      InitPipe(&pipes[i], maxRight + PIPE_SPACE, score);
    }
  }
}

void ResetPipes(Pipe *pipes, int count, int score) {
  for (int i = 0; i < count; i++) {
    InitPipe(&pipes[i], GetScreenWidth() + (i * PIPE_SPACE), score);
  }
}
