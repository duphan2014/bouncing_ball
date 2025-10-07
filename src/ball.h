#ifndef BALL_H
#define BALL_H

#if defined(__APPLE__)
#include <SDL.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#else
#error "Unsupported platform"
#endif

#include "platform.h"

typedef struct {
    int x, y;
    int vx, vy;
    int radius;
    Uint8 r, g, b;
} Ball;

void ball_init_array(Ball balls[], int count);
void ball_update(Ball *ball);
void ball_handle_wall_collision(Ball *ball, int winWidth, int winHeight, int *lives, int *gameOver);
int ball_check_platform_collision(Ball *ball, const Platform *platform);
void ball_handle_ball_collision(Ball balls[], int count);

#endif // BALL_H