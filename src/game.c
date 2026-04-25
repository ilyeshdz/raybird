#include "game.h"
#include "player.h"
#include "pipes.h"
#include "collision.h"
#include "renderer.h"
#include "raylib.h"

GameState InitGame() {
  GameState game_state = {
      .status = GAME_RUNNING,
      .score = 0,
      .player = {.position = {.y = (GetScreenHeight() - PLAYER_SIZE) / 2.0f,
                              .x = (GetScreenWidth() - PLAYER_SIZE) / 2.0f},
                 .size = {.x = PLAYER_SIZE, .y = PLAYER_SIZE},
                 .gravity = 500.0,
                 .jumpForce = 400.0,
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
  
  if (IsKeyPressed(KEY_SPACE) && state->status == GAME_OVER) {
    RestartGame(state);
  }
}

void DrawGame(GameState *state) {
  RenderGame(state);
}
