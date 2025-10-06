#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "ball.h"
#include "platform.h"

// Function declarations
void renderer_draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius);
void renderer_draw_filled_heart(SDL_Renderer *renderer, int x, int y, int size);
void renderer_draw_ball(SDL_Renderer *renderer, const Ball *ball);
void renderer_draw_platform(SDL_Renderer *renderer, const Platform *platform);
void renderer_draw_balls(SDL_Renderer *renderer, const Ball balls[], int count);

#endif // RENDERER_H