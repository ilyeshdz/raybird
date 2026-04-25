#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"
#include "pipes.h"
#include "player.h"

typedef enum { COLLISION_NONE, COLLISION_PIPE, COLLISION_BOUNDARY } CollisionType;

CollisionType CheckPipeCollision(const Player *player, const Pipe *pipes, int count);
CollisionType CheckBoundaryCollision(const Player *player);

#endif
