#include "pipes.h"
#include "raylib.h"

void InitPipe(Pipe *pipe, float xPos) {
  pipe->xPos = xPos;
  pipe->passed = false;
  int minGapY = MIN_GAP_Y;
  int maxGapY = GetScreenHeight() - PIPE_WIDTH - PIPE_GAP;
  int gapCenterY = GetRandomValue(minGapY, maxGapY);

  pipe->topRect = (Rectangle){.x = xPos,
                               .y = gapCenterY - PIPE_HEIGHT,
                               .width = PIPE_WIDTH,
                               .height = PIPE_HEIGHT};

  pipe->bottomRect = (Rectangle){.x = xPos,
                                  .y = gapCenterY + PIPE_GAP,
                                  .width = PIPE_WIDTH,
                                  .height = PIPE_HEIGHT};
}

void UpdatePipes(Pipe *pipes, int count) {
  for (int i = 0; i < count; i++) {
    pipes[i].bottomRect.x -= PIPE_SPEED * GetFrameTime();
    pipes[i].topRect.x -= PIPE_SPEED * GetFrameTime();

    if (pipes[i].topRect.x + PIPE_WIDTH < 0) {
      // Find the rightmost pipe
      float maxRight = 0.0f;
      for (int j = 0; j < count; j++) {
        if (pipes[j].topRect.x > maxRight) {
          maxRight = pipes[j].topRect.x;
        }
      }
      // Place the recycled pipe immediately after the rightmost pipe
      InitPipe(&pipes[i], maxRight + PIPE_SPACE);
    }
  }
}

void ResetPipes(Pipe *pipes, int count) {
  for (int i = 0; i < count; i++) {
    InitPipe(&pipes[i], GetScreenWidth() + (i * PIPE_SPACE));
  }
}
