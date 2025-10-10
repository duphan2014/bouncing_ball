#ifndef SCENE_H
#define SCENE_H

#if defined(__APPLE__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#error "Unsupported platform"
#endif
#include "sprite.h"
//#include "game.h"

typedef struct {
    int x, y;
    int vx, vy;
    Sprite* sprite;
} Cloud;

typedef struct {
    Cloud* clouds; // either pointer for dynamic size array or fixed size Cloud[10] clouds
    // add more as needed
    int cloud_count;
} Scene;

void scene_init(Scene* scene, SDL_Renderer* renderer, int winWidth, int winHeight);
void scene_init_clouds(Scene* scene, SDL_Renderer* renderer, int winWidth, int winHeight);
// void scene_draw(Scene* scene, SDL_Renderer* renderer);
// void scene_free(Scene* scene);

void scene_load_cloud(SDL_Renderer* renderer, Cloud* Cloud);
void scene_draw(Scene* scene, SDL_Renderer* renderer);
void scene_free(Scene* scene);
void scene_update_cloud(Scene* scene, int winWidth, int winHeight);
#endif