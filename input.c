#include "input.h"

void input_handle_event (SDL_Event *e) {
    printf("test");
    // quit game when press escape
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE) {
        printf("pressed escape key");
    }

    // Start game, restart game
    if (e->type == SDL_KEYDOWN && 
        //(e->key.keysym.sym == SDLK_RETURN) {
        (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_KP_ENTER)) {
        printf("pressed Enter");
    }

    if(e->type == SDL_KEYDOWN) {
        // Handle Alt+Enter for fullscreen toggle
        if(e->key.keysym.sym == SDLK_RETURN && (e->key.keysym.mod & KMOD_ALT)) {
            printf("pressed alt+Enter");
        }
    }
}