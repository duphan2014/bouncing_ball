#include "scene.h"
#include <stdio.h>

void scene_init(Scene* scene, SDL_Renderer* renderer){
    //<TODO>
    // build array to randomize cloud position and direction of floating
    // should crate a Cloud struct too scene->cloud
    //</TODO>
    scene->cloud_count = 1;
    scene->clouds = malloc(sizeof(Cloud) * scene->cloud_count);

    scene->clouds[0].x = 100; //scene->clouds[0] is not a pointer but a struct so use . instead of ->
    scene->clouds[0].y = 100;

    for(int i=0; i< scene->cloud_count; i++) {
        //load_cloud(renderer, sprite, x, y, width, height);
        scene_load_cloud(renderer, &scene->clouds[i]);
    }
}

void scene_load_cloud(SDL_Renderer* renderer, Cloud* cloud) {
    cloud->sprite =  sprite_load(renderer, "sprites/sprite.png", 0.1);
    if (!cloud->sprite) {
       printf("Cloud sprite failed to load!\n");
    }
}

void scene_draw(Scene* scene, SDL_Renderer* renderer) {
    for (int i = 0; i < scene->cloud_count; i++) {
        Cloud* c = &scene->clouds[i];
        if (c->sprite) {
            sprite_draw(renderer, c->sprite, c->x, c->y,
                        c->sprite->width, c->sprite->height);
        }
    }
}