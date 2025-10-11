#include "ui.h"
#include "renderer.h"
#include <stdio.h>

void ui_draw_score(SDL_Renderer *renderer, TTF_Font *font, int score) {
    SDL_Color white = {255, 255, 255};
    char scoreText[32];
    sprintf(scoreText, "Score: %d", score);

    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText, white);
    if (scoreSurface) {
        SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(scoreTexture);
    }
}

void ui_draw_high_score(SDL_Renderer *renderer, TTF_Font *font, int highScore) {
    SDL_Color white = {255, 255, 255};
    char highScoreText[32];
    sprintf(highScoreText, "High: %d", highScore);
    
    SDL_Surface *highScoreSurface = TTF_RenderText_Solid(font, highScoreText, white);
    if (highScoreSurface) {
        SDL_Texture *highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
        SDL_Rect highScoreRect = {10, 40, highScoreSurface->w, highScoreSurface->h};
        SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);
        SDL_FreeSurface(highScoreSurface);
        SDL_DestroyTexture(highScoreTexture);
    }
}

void ui_draw_lives(SDL_Renderer *renderer, int lives, int winWidth) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    for (int i = 0; i < lives; i++) {
        renderer_draw_filled_heart(renderer, winWidth - 30 - i*35, 25, 30);
    }
}

void ui_draw_start_screen(SDL_Renderer *renderer, TTF_Font *font, int winWidth, int winHeight) {
    SDL_Color white = {255, 255, 255};

    // Title
    SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "Gnuash 1.0", white);
    if (titleSurface) {
        SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_Rect titleRect = {winWidth/2 - titleSurface->w/2, winHeight/2 - titleSurface->h*2, titleSurface->w, titleSurface->h};
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_FreeSurface(titleSurface);
        SDL_DestroyTexture(titleTexture);
    }

    // Instructions
    SDL_Surface *instructSurface = TTF_RenderText_Solid(font, "Press Enter to Start", white);
    if (instructSurface) {
        SDL_Texture *instructTexture = SDL_CreateTextureFromSurface(renderer, instructSurface);
        SDL_Rect instructRect = {winWidth/2 - instructSurface->w/2, winHeight/2 - instructSurface->h/2, instructSurface->w, instructSurface->h};
        SDL_RenderCopy(renderer, instructTexture, NULL, &instructRect);
        SDL_FreeSurface(instructSurface);
        SDL_DestroyTexture(instructTexture);
    }
}

void ui_draw_pause_screen(SDL_Renderer *renderer, TTF_Font *font, int winWidth, int winHeight) {
    SDL_Color white = {255, 255, 255};

    // Title
    SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "PAUSED", white);
    if (titleSurface) {
        SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_Rect titleRect = {winWidth/2 - titleSurface->w/2, winHeight/2 - titleSurface->h*2, titleSurface->w, titleSurface->h};
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_FreeSurface(titleSurface);
        SDL_DestroyTexture(titleTexture);
    }

    // Instructions
    SDL_Surface *instructSurface = TTF_RenderText_Solid(font, "Press Enter to Continue", white);
    if (instructSurface) {
        SDL_Texture *instructTexture = SDL_CreateTextureFromSurface(renderer, instructSurface);
        SDL_Rect instructRect = {winWidth/2 - instructSurface->w/2, winHeight/2 - instructSurface->h/2, instructSurface->w, instructSurface->h};
        SDL_RenderCopy(renderer, instructTexture, NULL, &instructRect);
        SDL_FreeSurface(instructSurface);
        SDL_DestroyTexture(instructTexture);
    }
} 

void ui_draw_game_over_screen(SDL_Renderer *renderer, TTF_Font *font, int winWidth, int winHeight) {
    SDL_Color white = {255, 255, 255};

    // Game Over
    SDL_Surface *gameOverSurface = TTF_RenderText_Solid(font, "GAME OVER", white);
    if (gameOverSurface) {
        SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
        SDL_Rect gameOverRect = {winWidth/2 - gameOverSurface->w/2, winHeight/2 - gameOverSurface->h*2, gameOverSurface->w, gameOverSurface->h};
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
        SDL_FreeSurface(gameOverSurface);
        SDL_DestroyTexture(gameOverTexture);
    }

    // Restart instructions
    SDL_Surface *restartSurface = TTF_RenderText_Solid(font, "Press Enter to Restart", white);
    if (restartSurface) {
        SDL_Texture *restartTexture = SDL_CreateTextureFromSurface(renderer, restartSurface);
        SDL_Rect restartRect = {winWidth/2 - restartSurface->w/2, winHeight/2 - restartSurface->h/2, restartSurface->w, restartSurface->h};
        SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
        SDL_FreeSurface(restartSurface);
        SDL_DestroyTexture(restartTexture);
    }
}
