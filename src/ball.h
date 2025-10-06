#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

typedef struct {
    int x, y;
    int vx, vy;
    int radius;
    Uint8 r, g, b; // Color components
} Ball;

// Function declarations
void ball_init_array(Ball balls[], int count);
void ball_update(Ball *ball, int winWidth, int winHeight);
void ball_handle_wall_collision(Ball *ball, int winWidth, int winHeight, int *lives, int *gameOver);
int ball_check_platform_collision(Ball *ball, const struct Platform *platform);
void ball_handle_ball_collision(Ball balls[], int count);

#endif // BALL_H