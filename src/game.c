#include "game.h"
#include "player.h"
#include "pipes.h"
#include "collision.h"
#include "renderer.h"
#include "raylib.h"

GameState InitGame(void) {
  GameState game_state = {
      .status = GAME_RUNNING,
      .score = 0,
      .shouldQuit = false,
      .player = {.position = {.y = (GetScreenHeight() - PLAYER_SIZE) / 2.0f,
                              .x = (GetScreenWidth() - PLAYER_SIZE) / 2.0f},
                 .size = {.x = PLAYER_SIZE, .y = PLAYER_SIZE},
                 .gravity = PLAYER_GRAVITY,
                 .jumpForce = PLAYER_JUMP_FORCE,
                 .velocity = {0}}};

  ResetPipes(game_state.pipes, MAX_PIPES);

  return game_state;
}

void RestartGame(GameState *state) {
  state->player.position = (Vector2){
      .y = (GetScreenHeight() - PLAYER_SIZE) / 2.0f,
      .x = (GetScreenWidth() - PLAYER_SIZE) / 2.0f,
  };
  state->score = 0;
  state->player.velocity = (Vector2){0};
  state->status = GAME_RUNNING;

  ResetPipes(state->pipes, MAX_PIPES);
}

void UpdateGame(GameState *state) {
  if (IsKeyPressed(KEY_ESCAPE)) {
    if (state->status == GAME_RUNNING) {
      state->status = GAME_PAUSED;
    } else if (state->status == GAME_PAUSED) {
      state->status = GAME_RUNNING;
    }
  }
  
  if (state->status == GAME_RUNNING) {
    state->score += SCORE_INCREMENT * GetFrameTime();
    
    if (IsKeyPressed(KEY_SPACE)) {
      PlayerJump(&state->player);
    }
    
    UpdatePlayer(&state->player);
    UpdatePipes(state->pipes, MAX_PIPES);
    
    CollisionType collision = CheckPipeCollision(&state->player, state->pipes, MAX_PIPES);
    if (collision == COLLISION_NONE) {
      collision = CheckBoundaryCollision(&state->player);
    }
    
    if (collision != COLLISION_NONE) {
      state->status = GAME_OVER;
    }
  }
  
  if (state->status == GAME_PAUSED) {
    if (IsKeyPressed(KEY_R)) {
      RestartGame(state);
    }
    if (IsKeyPressed(KEY_A)) {
      state->shouldQuit = true;
    }
  }
  
  if (IsKeyPressed(KEY_SPACE) && state->status == GAME_OVER) {
    RestartGame(state);
  }
}

void DrawGame(GameState *state) {
  RenderGame(state);
}
