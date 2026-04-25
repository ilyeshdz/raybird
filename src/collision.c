#include "collision.h"
#include "player.h"
#include "pipes.h"
#include "raylib.h"

CollisionType CheckPipeCollision(const Player *player, const Pipe *pipes, int count) {
  Rectangle player_rect = GetPlayerRect((Player *)player);
  
  for (int i = 0; i < count; i++) {
    if (CheckCollisionRecs(pipes[i].topRect, player_rect) ||
        CheckCollisionRecs(pipes[i].bottomRect, player_rect)) {
      return COLLISION_PIPE;
    }
  }
  
  return COLLISION_NONE;
}

CollisionType CheckBoundaryCollision(const Player *player) {
  Rectangle player_rect = GetPlayerRect((Player *)player);
  
  if (player_rect.y < 0 || player_rect.y + player_rect.height > GetScreenHeight()) {
    return COLLISION_BOUNDARY;
  }
  
  return COLLISION_NONE;
}
