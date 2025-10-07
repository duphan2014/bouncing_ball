#ifndef GAME_H
#define GAME_H

#if defined(__APPLE__)
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#else
#error "Unsupported platform"
#endif

#include "ball.h"
#include "platform.h"

// Game constants
#define NUM_BALLS 5
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

// Game state enumeration
typedef enum {
    STATE_START,
    STATE_PLAYING,
    STATE_GAMEOVER
} GameState;

// Game context structure
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;

    GameState state;
    int score;
    int lives;
    int highScore;
    int winWidth;
    int winHeight;

    //Ball balls[NUM_BALLS];
    //Platform platform;

    // Audio
    Mix_Chunk *soundHitPlatform;
    Mix_Chunk *soundHitBottom;
    Mix_Chunk *soundGameOver;
    
    int running;
} Game;

//Function declarations
int game_init(Game *game);
void game_load_highscore(Game *game);
void game_run(Game *game);
void game_update(Game *game);
void game_render(Game *game);
void game_save_highscore(Game *game);
void game_reset(Game *game);
void game_cleanup(Game *game);

#endif // GAME_H