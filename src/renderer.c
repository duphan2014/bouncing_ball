#include "renderer.h"

void renderer_draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    for (int w = -radius; w <= radius; w++) {
        for (int h = - radius; h <= radius; h++) {
            if (w*w + h*h <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
            }
        }
    }
}

void renderer_draw_ball(SDL_Renderer *renderer, const Ball *ball) {
    // Big circle
    SDL_SetRenderDrawColor(renderer, ball->r, ball->g, ball->b, 255);
    renderer_draw_filled_circle(renderer, ball->x, ball->y, ball->radius);

    // small circle (highlight effect)
    SDL_SetRenderDrawColor(renderer, ball->r-100, ball->g-100, ball->b-100, 200);
    renderer_draw_filled_circle(renderer, ball->x - ball->radius/3, ball->y - ball->radius/3, ball->radius/4);
}

void renderer_draw_balls(SDL_Renderer *renderer, const Ball balls[], int count) {
    for (int i = 0; i < count; i++){
        renderer_draw_ball(renderer, &balls[i]);
    }
}

void renderer_draw_filled_heart(SDL_Renderer *renderer, int x, int y, int size) {
    // Draw two circles for the top of the heart
    renderer_draw_filled_circle(renderer, x - size/4, y, size/4);
    renderer_draw_filled_circle(renderer, x + size/4, y, size/4);

    // Draw a triangle for the bottom
    // Fill triangle (approximate by drawing lines)
    for (int i = 0; i < size/2; i++) {
        int px1 = x - size/2 + i;
        int px2 = x + size/2 - i;
        int py = y + i;
        SDL_RenderDrawLine(renderer, px1, py, px2, py);
    }
}

void renderer_draw_platform(SDL_Renderer *renderer, const Platform *platform){
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Cyan
    // Simulate bend
    SDL_Rect rect = {
        platform->x,
        platform->y + platform->bendOffset,
        platform->width,
        platform->height - platform->bendOffset
    };
    SDL_RenderFillRect(renderer, &rect);
}