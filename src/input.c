#include "input.h"
#include "platform.h"

void input_handle_events (Game *game, SDL_Event *event) {
    // check for one-time event from th event queue
    while (SDL_PollEvent(event)) {
        if(event->type == SDL_QUIT) {
            game->running = 0;
        }
        
        if (event->type == SDL_KEYDOWN) {
            //Quit game when press escape
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                game->running = 0;
            }
            //Start game, restart game
            if (event->key.keysym.sym == SDLK_RETURN || event->key.keysym.sym == SDLK_KP_ENTER) {
                if (game->state == STATE_START) {
                    game->state = STATE_PLAYING;
                } else if (game->state == STATE_GAMEOVER) {
                    game_reset(game);
                    game->state = STATE_PLAYING;
                }
            }

            // HANDLE ALT+ENTER for fullscreen toggle
            if (event->key.keysym.sym == SDLK_RETURN && (event->key.keysym.mod & KMOD_ALT)) {
                Uint32 flags = SDL_GetWindowFlags(game->window);
                if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                    SDL_SetWindowFullscreen(game->window, 0); // windowed
                } else {
                    SDL_SetWindowFullscreen(game->window, SDL_WINDOW_FULLSCREEN_DESKTOP); // fullscreened
                }

                // Update window size variables
                SDL_GetWindowSize(game->window, &game->winWidth, &game->winHeight);
                // Update platform position to stay at the bottom
                game->platform.y = game->winHeight - game->platform.height;
                
                // Restart position of balls, otherwise hard to change them proportionally
                ball_init_array(game->balls, NUM_BALLS);
            }
        }
    }
}

// for continuous key press
void input_handle_keyboard (Game *game, const Uint8 *keystate) {
    if (game->state == STATE_PLAYING) {
        platform_handle_input(&game->platform, keystate, game->winWidth);
    }
}