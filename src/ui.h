#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

// Function declarations
void ui_draw_score(SDL_Renderer *renderer, TTF_Font *font, int score);
void ui_draw_high_score(SDL_Renderer *renderer, TTF_Font *font, int highScore);
void ui_draw_lives(SDL_Renderer *renderer, int lives, int winWidth);
void ui_draw_start_screen(SDL_Renderer *renderer, TTF_Font *font, int winWidth, int winHeight);
void ui_draw_game_over_screen(SDL_Renderer *renderer, TTF_Font *font, int winWidth, int winHeight);

#endif // UI_H