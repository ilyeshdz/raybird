#include "game.h"
#include "player.h"
#include "pipes.h"
#include "particles.h"
#include "collision.h"
#include "renderer.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define HIGH_SCORE_FILE "highscore.txt"

static void SpawnPlayerParticles(ParticleSystem *particles, const Player *player, ParticleType type, int count) {
  for (int i = 0; i < count; i++) {
    Vector2 particlePos = {
      .x = player->position.x + player->size.x / 2,
      .y = player->position.y + player->size.y / 2
    };
    SpawnParticle(particles, particlePos, type);
  }
}

static int LoadHighScore(void) {
  FILE *file = fopen(HIGH_SCORE_FILE, "r");
  if (file) {
    int score = 0;
    if (fscanf(file, "%d", &score) == 1) {
      fclose(file);
      return score;
    }
    fclose(file);
  }
  return 0;
}

static void SaveHighScore(int score) {
  FILE *file = fopen(HIGH_SCORE_FILE, "w");
  if (file) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

GameState InitGame(void) {
  GameState game_state = {
      .status = GAME_RUNNING,
      .score = 0,
      .highScore = LoadHighScore(),
      .shouldQuit = false,
      .debugMode = false,
      .lastMilestone = 0,
      .player = {.position = {.y = (GetScreenHeight() - PLAYER_SIZE) / 2.0f,
                              .x = (GetScreenWidth() - PLAYER_SIZE) / 2.0f},
                 .size = {.x = PLAYER_SIZE, .y = PLAYER_SIZE},
                 .gravity = PLAYER_GRAVITY,
                 .jumpForce = PLAYER_JUMP_FORCE,
                 .velocity = {0}}};

  ResetPipes(game_state.pipes, MAX_PIPES, 0);
  InitParticleSystem(&game_state.particles);

  return game_state;
}

void RestartGame(GameState *state) {
  state->player.position = (Vector2){
      .y = (GetScreenHeight() - PLAYER_SIZE) / 2.0f,
      .x = (GetScreenWidth() - PLAYER_SIZE) / 2.0f,
  };
  state->score = 0;
  state->lastMilestone = 0;
  state->player.velocity = (Vector2){0};
  state->status = GAME_RUNNING;

  ResetPipes(state->pipes, MAX_PIPES, 0);
  ResetParticles(&state->particles);
}

void UpdateGame(GameState *state) {
  // Debug mode toggle
  if (IsKeyPressed(KEY_D)) {
    state->debugMode = !state->debugMode;
  }

  // Debug cheats
  if (state->debugMode) {
    if (IsKeyPressed(KEY_ONE)) {
      state->score += 5;
    }
    if (IsKeyPressed(KEY_TWO)) {
      state->score += 10;
    }
    if (IsKeyPressed(KEY_THREE)) {
      state->score += 25;
    }
    if (IsKeyPressed(KEY_ZERO)) {
      state->score = 0;
    }
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    if (state->status == GAME_RUNNING) {
      state->status = GAME_PAUSED;
    } else if (state->status == GAME_PAUSED) {
      state->status = GAME_RUNNING;
    }
  }

  if (state->status == GAME_RUNNING) {
    if (IsKeyPressed(KEY_SPACE)) {
      PlayerJump(&state->player);
      SpawnPlayerParticles(&state->particles, &state->player, PARTICLE_FEATHER, 3);
    }

    UpdatePlayer(&state->player);
    UpdatePipes(state->pipes, MAX_PIPES, state->score);
    UpdateParticles(&state->particles, GetFrameTime());

    // Check if player passed through any pipe
    for (int i = 0; i < MAX_PIPES; i++) {
      if (!state->pipes[i].passed) {
        // Check if player has passed the pipe (player x > pipe x + pipe width)
        if (state->player.position.x > state->pipes[i].topRect.x + state->pipes[i].topRect.width) {
          state->pipes[i].passed = true;
          state->score += SCORE_INCREMENT;

          // Check for milestones
          int milestone = (state->score / 10) * 10;
          if (milestone > state->lastMilestone && milestone % 10 == 0) {
            state->lastMilestone = milestone;
            // Spawn celebration particles
            SpawnPlayerParticles(&state->particles, &state->player, PARTICLE_EXPLOSION, 30);
          }
        }
      }
    }

    CollisionType collision = CheckPipeCollision(&state->player, state->pipes, MAX_PIPES);
    if (collision == COLLISION_NONE) {
      collision = CheckBoundaryCollision(&state->player);
    }

    if (collision != COLLISION_NONE) {
      state->status = GAME_OVER;
      SpawnPlayerParticles(&state->particles, &state->player, PARTICLE_EXPLOSION, 20);
      // Save high score if current score is higher
      if (state->score > state->highScore) {
        state->highScore = state->score;
        SaveHighScore(state->highScore);
      }
    }
  }

  if (state->status == GAME_PAUSED) {
    if (IsKeyPressed(KEY_R)) {
      RestartGame(state);
    }
    if (IsKeyPressed(KEY_Q)) {
      state->shouldQuit = true;
    }
  }

  // Update particles even when paused or game over (for smooth animation)
  UpdateParticles(&state->particles, GetFrameTime());

  if (IsKeyPressed(KEY_SPACE) && state->status == GAME_OVER) {
    RestartGame(state);
  }
}

void DrawGame(GameState *state) {
  RenderGame(state);
}
