#ifndef UI_H
#define UI_H

#if defined(__APPLE__)
#include <SDL.h>
#include <SDL_ttf.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#error "Unsupported platform"
#endif

#include "game.h"

void ui_draw_score(SDL_Renderer *renderer, TTF_Font *font, int score)
void ui_draw_high_score(SDL_Renderer *renderer, TTF_Font *font, int highScore)
void ui_draw_lives(SDL_Renderer *renderer, int lives, int winWidth)
void ui_draw_start_screen(SDL_Renderer *renderer, TTF_Font *font, int winWidth, int winHeight)
void ui_draw_game_over_screen(SDL_Renderer *renderer, TTF_Font *font, int winWidth, int winHeight)

#endif //UI_H