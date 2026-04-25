#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"
#include "pipes.h"

void RenderGame(const GameState *state);
void RenderPlayer(const Player *player);
void RenderPipes(const Pipe *pipes, int count);
void RenderUI(const GameState *state);
void RenderPauseMenu(const GameState *state);

#endif
