#ifndef SPRITE_H
#define SPRITE_H

#if defined(__APPLE__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#error "Unsupported platform"
#endif

typedef struct {
    SDL_Texture* texture;
    int width;
    int height;
} Sprite;

Sprite* sprite_load(SDL_Renderer* renderer, const char* path, float scaleRatio);
void sprite_draw(SDL_Renderer* renderer, Sprite* sprite, int x, int y, int w, int h);
void sprite_free(Sprite* sprite);

#endif