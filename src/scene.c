#include "scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void scene_init(Scene* scene, SDL_Renderer* renderer, int winWidth, int winHeight) {
    scene_init_clouds(scene, renderer, winWidth, winHeight);
    //<TODO> other inits to come e.g. scene_init_trees, scene_init_mountain
}

void scene_init_clouds(Scene* scene, SDL_Renderer* renderer, int winWidth, int winHeight){
    //<TODO>
    // build array to randomize cloud position and direction of floating
    // should crate a Cloud struct too scene->cloud
    //</TODO>
    srand(time(NULL));
    scene->cloud_count = 7;
    scene->clouds = malloc(sizeof(Cloud) * scene->cloud_count);

    // randomize initial positions of clouds
    for (int i = 0; i < scene->cloud_count; i++) {
        scene->clouds[i].x = rand() % winWidth; // within range 0 - width-1. //scene->clouds[0] is not a pointer but a struct so use . instead of ->
        int minY = (int)((float)winHeight * 0.1f);
        int maxY = (int)((float)winHeight * 0.2f);
        scene->clouds[i].y = minY + rand() % (maxY - minY);
        //scene->clouds[i].y = rand() % (int)((float)winHeight*0.2); 
    }
    //scene->clouds[0].x = 100; 
    //scene->clouds[0].y = 100;

    for(int i=0; i< scene->cloud_count; i++) {
        //load_cloud(renderer, sprite, x, y, width, height);
        //scene_load_cloud(renderer, &scene->clouds[i]);

        scene->clouds[i].sprite =  sprite_load(renderer, "sprites/sprite.png", 0.1);
        if (!scene->clouds[i].sprite) {
        printf("Cloud sprite failed to load!\n");
        }
    }
}

// void scene_load_cloud(SDL_Renderer* renderer, Cloud* cloud) {
//     cloud->sprite =  sprite_load(renderer, "sprites/sprite.png", 0.1);
//     if (!cloud->sprite) {
//        printf("Cloud sprite failed to load!\n");
//     }
// }

void scene_draw(Scene* scene, SDL_Renderer* renderer) {
    for (int i = 0; i < scene->cloud_count; i++) {
        Cloud* c = &scene->clouds[i];
        if (c->sprite) {
            sprite_draw(renderer, c->sprite, c->x, c->y,
                        c->sprite->width, c->sprite->height);
        }
    }
}

void scene_free(Scene* scene) {
    //TODO sprite free
    for(int i = 0; i < scene->cloud_count; i++){
        sprite_free(scene->clouds[i].sprite);
    }
    free(scene);
}