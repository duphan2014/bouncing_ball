#ifndef RENDERER_H
#define RENDERER_H

#if defined(__APPLE__)
#include <SDL.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#else
#error "Unsupported platform"
#endif

#include "ball.h"
#include "platform.h"

void renderer_draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius);
void renderer_draw_ball(SDL_Renderer *renderer, const Ball *ball);
void renderer_draw_balls(SDL_Renderer *renderer, const Ball balls[], int count);

void renderer_draw_filled_heart(SDL_renderer *renderer, int x, int y, int size);

void renderer_draw_platform(SDL_Renderer *renderer, const Platform *platform);

#endif // RENDERER_H