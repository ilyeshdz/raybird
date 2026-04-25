#include "particles.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

void InitParticleSystem(ParticleSystem *system) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    system->particles[i].active = false;
  }
  system->count = 0;
}

void SpawnParticle(ParticleSystem *system, Vector2 position, ParticleType type) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!system->particles[i].active) {
      Particle *p = &system->particles[i];
      p->position = position;
      p->type = type;
      p->active = true;
      p->lifetime = PARTICLE_LIFETIME;

      if (type == PARTICLE_FEATHER) {
        p->size = (Vector2){10.0f, 10.0f};
        p->color = WHITE;
        p->velocity = (Vector2){
          .x = (float)GetRandomValue(-50, 50),
          .y = (float)GetRandomValue(-100, -50)
        };
        p->rotation = 0.0f;
        p->rotationSpeed = (float)GetRandomValue(-5, 5);
      } else if (type == PARTICLE_EXPLOSION) {
        p->size = (Vector2){(float)GetRandomValue(5, 15), (float)GetRandomValue(5, 15)};
        p->color = (Color){
          .r = (unsigned char)GetRandomValue(200, 255),
          .g = (unsigned char)GetRandomValue(100, 200),
          .b = 0,
          .a = 255
        };
        float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
        float speed = (float)GetRandomValue(100, 300);
        p->velocity = (Vector2){
          .x = cosf(angle) * speed,
          .y = sinf(angle) * speed
        };
        p->rotation = 0.0f;
        p->rotationSpeed = (float)GetRandomValue(-10, 10);
      }

      system->count++;
      break;
    }
  }
}

void UpdateParticles(ParticleSystem *system, float deltaTime) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    Particle *p = &system->particles[i];
    if (p->active) {
      p->lifetime -= deltaTime;
      p->position.x += p->velocity.x * deltaTime;
      p->position.y += p->velocity.y * deltaTime;
      p->rotation += p->rotationSpeed * deltaTime;

      // Apply gravity to feathers
      if (p->type == PARTICLE_FEATHER) {
        p->velocity.y += 200.0f * deltaTime;
      }

      // Fade out
      p->color.a = (unsigned char)(255 * (p->lifetime / PARTICLE_LIFETIME));

      if (p->lifetime <= 0.0f) {
        p->active = false;
        system->count--;
      }
    }
  }
}

void RenderParticles(const ParticleSystem *system) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    const Particle *p = &system->particles[i];
    if (p->active) {
      Rectangle rect = {
        .x = p->position.x,
        .y = p->position.y,
        .width = p->size.x,
        .height = p->size.y
      };

      if (p->type == PARTICLE_FEATHER) {
        DrawRectanglePro(rect, (Vector2){p->size.x / 2, p->size.y / 2}, 
                         p->rotation, p->color);
      } else {
        DrawRectanglePro(rect, (Vector2){p->size.x / 2, p->size.y / 2}, 
                         p->rotation, p->color);
      }
    }
  }
}

void ResetParticles(ParticleSystem *system) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    system->particles[i].active = false;
  }
  system->count = 0;
}
