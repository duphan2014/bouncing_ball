#include "game.h"
#include "audio.h"
#include "input.h"
#include "renderer.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int game_init(Game *game) {
    srand(time(NULL));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize TTF
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return -1;
    }

    // Load font
    game->font = TTF_OpenFont("fonts/DancingScript-VariableFont_wght.ttf", 32);
    if (!game->font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return -1;
    }

    // ===== SOUND =====
    // Initialize audio
    if (audio_init() < 0) {
        return -1;
    }

    // Load sounds
    game->soundHitPlatform = audio_load_sound("sound/boing_x.wav");
    game->soundHitBottom = audio_load_sound("sounds/blip.wav");
    game->soundGameOver = audio_load_sound("sounds/floop2_x.wav");

    // ==== WINDOW =====
    // Initialize window dimensions
    game->winWidth = WINDOW_WIDTH;
    game->winHeight = WINDOW_HEIGHT;

    // Create window
    game->window = SDL_CreateWindow("Gnuash",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    game->winWidth, game->winHeight,
                                    SDL_WINDOW_SHOWN);
    if (!game->window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // create renderer
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_RendererInfo info;
    SDL_GetRendererInfo(game->renderer, &info);
    printf("SDL picked renderer: %s\n", info.name);

    // Initialize game state
    game->state = STATE_START;
    game->score = 0;
    game->lives = 5;
    game->running = 1;

    // Load high score
    game_load_highscore(game);

    // Initialize game objects
    ball_init_array(game->balls, NUM_BALLS); // balls ia already an array, which decays to a pointer. pass address of first element.
    platform_init(&game->platform, game->winWidth, game->winHeight);

    return 0;
}
void game_cleanup(Game *game) {
    // Clean up audio
    audio_free_sound(game->soundHitPlatform);
    audio_free_sound(game->soundHitBottom);
    audio_free_sound(game->soundGameOver);
    audio_cleanup();

    // Clean up SDL
    if (game->renderer) SDL_DestroyRenderer(game->renderer);
    if (game->window) SDL_DestroyWindow(game->window);

    // Clean up TTF
    if (game->font) TTF_CloseFont(game->font);
    TTF_Quit();

    SDL_Quit();

}
void game_run(Game *game) {
    SDL_Event event;

    while(game->running) {
        input_handle_events(game, &event);

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        input_handle_keyboard(game, keystate);

        game_update(game);
        game_render(game);

        // Delay to control frame rate (16ms ~ 60 FPS)
        SDL_Delay(16);
    }

}
void game_update(Game *game) {
    if (game->state == STATE_PLAYING) {
        // update platform, for visual effect bend vibrate or still
        platform_update(&game->platform, game->winWidth);

        //update balls and handle collisions
        for (int i = 0; i < NUM_BALLS; i++) {
            //moving balls
            ball_update(&game->balls[i]);

            int gameOver = 0;
            ball_handle_wall_collision(&game->balls[i], game->winWidth, game->winHeight, &game->lives, &gameOver);
            
            if (gameOver) {
                audio_play_sound(game->soundGameOver);
                game->state = STATE_GAMEOVER;
                game_save_highscore(game);
            }

            // Handle bottom collision sound --> <TO BE REFACTOR>, currently ball_handle_wall_collision() only handle direction change
            if (game->balls[i].y + game->balls[i].radius >= game->winHeight) {
                audio_play_sound(game->soundHitBottom);
            }

            // Platform collision
            if (ball_check_platform_collision(&game->balls[i], &game->platform)) {
                platform_handle_collision(&game->platform);
                audio_play_sound(game->soundHitPlatform);
                game->score++;
            }
        }

        // Ball-to-ball collisions, to divert their paths
        ball_handle_ball_collision(game->balls, NUM_BALLS);
    }
}
void game_render(Game *game) {
    // Set background color (black)
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    // Draw balls
    renderer_draw_balls(game->renderer, game->balls, NUM_BALLS);

    // Draw platform
    renderer_draw_platform(game->renderer, &game->platform);

    // Draw UI elements
    ui_draw_score(game->renderer, game->font, game->score);
    ui_draw_high_score(game->renderer, game->font, game->highScore);
    ui_draw_lives(game->renderer, game->lives, game->winWidth);

    // Draw game state screens
    if (game->state == STATE_START) {
        ui_draw_start_screen(game->renderer, game->font, game->winWidth, game->winHeight);
    } else if (game->state == STATE_GAMEOVER) {
        ui_draw_game_over_screen(game->renderer, game->font, game->winWidth, game->winHeight);
    }

    // Present everything
    SDL_RenderPresent(game->renderer);
}
void game_reset(Game *game) {
    game->score = 0;
    game->lives = 5;
    ball_init_array(game->balls, NUM_BALLS);
    platform_init(&game->platform, game->winWidth, game->winHeight); //-> higher precedence than & so it means &(game->platform) aka get the address of the platform
}
void game_save_highscore(Game *game) {
    if (game->score > game->highScore) {
        game->highScore = game->score;
        FILE *f = fopen("highscore.txt", "w");
        if (f) {
            fprintf(f, "%d", game->highScore);
            fclose(f);
        }
    }

}
void game_load_highscore(Game *game) {
    FILE *f = fopen("highscore.txt", "r");
    if (f) {
        fscanf(f, "%d", &game->highScore);
        fclose(f);
    } else {
        game->highScore = 0;
    }
}