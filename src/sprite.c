#include "sprite.h"
#include <stdio.h>
#include <stdio.h>

Sprite* sprite_load(SDL_Renderer* renderer, const char* path, float scaleRatio) {
    Sprite* sprite = malloc(sizeof(Sprite));
    if (!sprite) return NULL;

    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("Failed to load image %s: %s\n", path, IMG_GetError());
        free(sprite);
        return NULL;
    }

    // scale image
    SDL_Surface* scaledSurface = SDL_CreateRGBSurface(
        0, surface->w*scaleRatio, surface->h*scaleRatio, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000
    );
    if (!scaledSurface) {
        printf("Failed to create scaled surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        free(sprite);
        return NULL;
    }
    SDL_BlitScaled(surface, NULL, scaledSurface, NULL);
    SDL_FreeSurface(surface);
    
    sprite->texture = SDL_CreateTextureFromSurface(renderer, scaledSurface);
    if (!sprite->texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        free(sprite);
        return NULL;
    }
    sprite->width = scaledSurface->w;
    sprite->height = scaledSurface->h;
    SDL_FreeSurface(scaledSurface);

    return sprite;
}

// should not use ratio because it requires extra calculation at every frame
void sprite_draw(SDL_Renderer* renderer, Sprite* sprite, int x, int y, int w, int h) {
    SDL_Rect dest = { x, y, w, h };
    SDL_RenderCopy(renderer, sprite->texture, NULL, &dest);
}

void sprite_free(Sprite* sprite) {
    if (sprite) {
        if (sprite->texture) SDL_DestroyTexture(sprite->texture);
        free(sprite);
    }
}

