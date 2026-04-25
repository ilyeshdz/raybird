#ifndef PARTICLES_H
#define PARTICLES_H

#include "raylib.h"

#define MAX_PARTICLES 100
#define PARTICLE_LIFETIME 1.0f

typedef enum {
  PARTICLE_FEATHER,
  PARTICLE_EXPLOSION
} ParticleType;

typedef struct {
  Vector2 position;
  Vector2 velocity;
  Vector2 size;
  Color color;
  float lifetime;
  float rotation;
  float rotationSpeed;
  ParticleType type;
  bool active;
} Particle;

typedef struct {
  Particle particles[MAX_PARTICLES];
  int count;
} ParticleSystem;

void InitParticleSystem(ParticleSystem *system);
void SpawnParticle(ParticleSystem *system, Vector2 position, ParticleType type);
void UpdateParticles(ParticleSystem *system, float deltaTime);
void RenderParticles(const ParticleSystem *system);
void ResetParticles(ParticleSystem *system);

#endif
