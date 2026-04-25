#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"
#include "pipes.h"

#define UI_FONT_SIZE 20
#define UI_SCORE_X 25
#define UI_SCORE_Y 25
#define PAUSE_TITLE_SIZE 40
#define PAUSE_MENU_SIZE 20
#define PAUSE_MENU_SPACING 30

void RenderGame(const GameState *state);
void RenderPlayer(const Player *player);
void RenderPipes(const Pipe *pipes, int count);
void RenderUI(const GameState *state);
void RenderPauseMenu(const GameState *state);

#endif
