#include "ball.h"
#include "platform.h"
#include <stdlib.h>

void ball_init_array(Ball balls[], int count) {
    Ball initial_balls[5] = {
        {100, 100, 6, 4, 20, 250, 0, 0},
        {200, 150, -4, 6, 20, 250, 0, 0},
        {300, 200, 8, -6, 20, 0, 250, 0},
        {400, 250, -6, -4, 20, 0, 250, 0},
        {500, 300, 4, 8, 20, 0, 0, 250}
    };

    for (int i = 0; i < count && i < 5; i++) {
        balls[i] = initial_balls[i];
    }
}

void ball_update(Ball *ball) {
    ball->x += ball->vx;
    ball->y += ball->vy;
}

void ball_handle_wall_collision(Ball *ball, int winWidth, int winHeight, int *lives, int *gameOver) {
    // Side walls collision
    if (ball->x - ball->radius <= 0 || ball->x + ball->radius >= winWidth) {
        ball->vx = -ball->vx;
    }

    // top wall collision
    if (ball->y - ball->radius <= 0) {
        ball->vy = -ball->vy;
    }

    // bottom wall collision -lose life
    if (ball->y + ball->radius >= winHeight) {
        (*lives)--;
        if (*lives <= 0) {
            *gameOver = 1;
        }
        ball->vy = -ball->vy;
    }
}

int ball_check_platform_collision(Ball *ball, const Platform *platform) {
    if (ball->y + ball->radius >= platform->y && // top edge
        ball->x >= platform->x && // left edge
        ball->x <= platform->x + platform->width && // right edge
        ball->y + ball->radius <= platform->y + platform->height) { // bottom edge

            ball->vy = -ball->vy;
            ball->y = platform->y - ball->radius; // prevent sticking
            return 1; // collision occured
    }
    return 0; // No collision
}

void ball_handle_ball_collision(Ball balls[], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            int dx = balls[i].x - balls[j].x;
            int dy = balls[i].y - balls[j].y;
            int distanceSq = dx * dx + dy * dy
            int radiusSum = balls[i].radius + balls[j].radius;

            if (distanceSq <= radiusSum * radiusSum) {
                // Simple velocity swap
                int tempVx = balls[i].vx;
                int tempVy = balls[i].vy;
                balls[i].vx = balls[j].vx;
                balls[i].vy = balls[j].vy;
                balls[j].vx = tempVx;
                balls[j].vy = tempVy;   
            }
        }
    }
}