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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int x, y;
  int vx, vy;
  int radius;
  Uint8 r, g, b; // Color components
} Ball;

typedef struct {
    int x, y;
    int width, height;
    int speed;
    int bendOffset;     // For bending effect
    int vibrationTimer; // For vibration duration
} Platform;

enum GameState { STATE_START, STATE_PLAYING, STATE_GAMEOVER };
enum GameState gameState = STATE_START;

#define NUM_BALLS 5
Ball balls[NUM_BALLS] = {
    {100, 100, 6, 4, 20, 250, 0, 0},
    {200, 150, -4, 6, 20, 250, 0, 0},
    {300, 200, 8, -6, 20, 0, 250, 0},
    {400, 250, -6, -4, 20, 0, 250, 0},
    {500, 300, 4, 8, 20, 0, 0 , 250}
};

// Function to draw a filled circle
void SDL_RenderFillCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
  for (int w = -radius; w <= radius; w++) {
    for (int h = - radius; h <= radius; h++) {
      if (w*w + h*h <= radius*radius) {
        SDL_RenderDrawPoint(renderer, cx + w, cy + h);
      }
    }
  }
}

void SDL_RenderFillHeart(SDL_Renderer *renderer, int x, int y, int size) {
    // Draw two circles for the top of the heart
    SDL_RenderFillCircle(renderer, x - size/4, y, size/4);
    SDL_RenderFillCircle(renderer, x + size/4, y, size/4);

    // Draw a triangle for the bottom
    // show 3 corners of the triangle that forms the bottom part of the heart
    //SDL_Point points[3] = {
    //    {x - size/2, y},
    //    {x + size/2, y},
    //    {x, y + size/2}
    //};
    // Fill triangle (approximate by drawing lines)
    for (int i = 0; i < size/2; i++) {
        int px1 = x - size/2 + i;
        int px2 = x + size/2 - i;
        int py = y + i;
        SDL_RenderDrawLine(renderer, px1, py, px2, py);
    }
}

int score = 0, lives = 5, highScore = 0;
TTF_Font *font;

int main(int argc, char* argv[]) {
  
  srand(time(NULL));

  // Load high score
  FILE *f = fopen("highscore.txt", "r");
  if (f) { fscanf(f, "%d", &highScore); fclose(f); }

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  //if (SDL_Init(SDL_INIT_AUDIO) < 0) {
  //  printf("SDL Audio could not initialize! SDL_Error: %s\n", SDL_GetError());
  //  return 1;
  //}

  // Initialize text
  if (TTF_Init() == -1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    return 1;
  }
  font = TTF_OpenFont("fonts/DancingScript-VariableFont_wght.ttf", 32);
  if (!font) {
    printf("Failed to load font: %s\n", TTF_GetError());
    return 1;
  }

  // initialize audio
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }

  Mix_Chunk *soundHitPlatform = Mix_LoadWAV("sounds/boing_x.wav");
  if (!soundHitPlatform) {
    printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
  }

  Mix_Chunk *soundHitBottom = Mix_LoadWAV("sounds/blip.wav");
  if (!soundHitBottom) {
    printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
  }

  Mix_Chunk *soundGameOver = Mix_LoadWAV("sounds/floop2_x.wav");
  if (!soundGameOver) {
    printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
  }

  int winWidth = 1024; //640;
  int winHeight = 768; //480;

  // initialize platform
  Platform platform = { winWidth / 2 - 50, winHeight - 30, 100, 15, 24, 0, 0};

  // Create a window
  SDL_Window* window = SDL_CreateWindow("Basic Graphics in C",
		                        SDL_WINDOWPOS_CENTERED,
					                  SDL_WINDOWPOS_CENTERED,
					                  winWidth, winHeight,
					                  SDL_WINDOW_SHOWN);

  if (!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  // Create a renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  printf("SDL picked renderer: %s\n", info.name);

  // Game loop flag
  int running = 1;
  SDL_Event e;

  while (running) {
    // debug currently pressed key
    if (e.type == SDL_KEYDOWN) {
      printf("Key pressed: %d\n", e.key.keysym.sym);
    }

    // quit game when click X button
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

    // quit game when press escape
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
      running = 0;
    }

    // Start game, restart game
    if (e.type == SDL_KEYDOWN && 
      //e.key.keysym.sym == SDLK_RETURN) {
      (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)) {
      if (gameState == STATE_START) {
          gameState = STATE_PLAYING;
          // Reset score, lives, balls, platform as needed
      } else if (gameState == STATE_GAMEOVER) {
          gameState = STATE_PLAYING;
          score = 0;
          lives = 5;
          // Reset balls and platform positions as needed
      }
    }

    if(e.type == SDL_KEYDOWN) {
      // Handle Alt+Enter for fullscreen toggle
      if(e.key.keysym.sym == SDLK_RETURN && (e.key.keysym.mod & KMOD_ALT)) {
        // Before resizing
        //int oldWinWidth = winWidth;
        //int oldWinHeight = winHeight;
        Uint32 flags = SDL_GetWindowFlags(window);
        if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
          SDL_SetWindowFullscreen(window, 0); // Windowed
          //for (int i = 0; i < NUM_BALLS; i++) {
            // Scale position proportionally
          //  balls[i].x = balls[i].x * winWidth / oldWinWidth;
          //  balls[i].y = balls[i].y * winHeight / oldWinHeight;
          //}
        } else {
          SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); //FUllscreen
        
        }
      }
      // update window size variables
      SDL_GetWindowSize(window, &winWidth, &winHeight);
      // Update platform position to stay at the bottom
      platform.y = winHeight - platform.height;
    }

    if (gameState == STATE_PLAYING) {
      //keyboard handling
      const Uint8 *keystate = SDL_GetKeyboardState(NULL);
      if (keystate[SDL_SCANCODE_LEFT]) {
        platform.x -= platform.speed;
      }
      
      if (keystate[SDL_SCANCODE_RIGHT]) {
        platform.x += platform.speed;
      }

      // Keep platform within window bounds
      if (platform.x < 0) platform.x = 0;
      if (platform.x + platform.width > winWidth) platform.x = winWidth - platform.width;

      // collision - walls and platform
      for (int i = 0; i < NUM_BALLS; i++){
        balls[i].x += balls[i].vx;
        balls[i].y += balls[i].vy;

        // Wall collision - can bounce off side walls
        if (balls[i].x - balls[i].radius <= 0 || balls[i].x + balls[i].radius >= winWidth) {
            balls[i].vx = -balls[i].vx;
        }

        // Wall collision - top
        if (balls[i].y - balls[i].radius <= 0) {
          balls[i].vy = -balls[i].vy;
        }

        // Wall collision - bottom - lose lives
        if (balls[i].y + balls[i].radius >= winHeight) {
          //Play sounds
          Mix_PlayChannel(-1, soundHitBottom, 0);

          lives--;
          if (lives <= 0) {
            Mix_PlayChannel(-1, soundGameOver, 0);
            gameState = STATE_GAMEOVER;
          }  
            
          balls[i].vy = -balls[i].vy;
        }

        if (gameState == STATE_GAMEOVER) {
          if (score > highScore) {
            highScore = score;
            FILE *f = fopen("highscore.txt", "w");
            if (f) { fprintf(f, "%d", highScore); fclose(f); }
          }
        }

        // Platform collision
        if (balls[i].y + balls[i].radius >= platform.y &&
            balls[i].x >= platform.x &&
            balls[i].x <= platform.x + platform.width &&
            balls[i].y + balls[i].radius <= platform.y + platform.height) {
              balls[i].vy = -balls[i].vy;
              balls[i].y = platform.y - balls[i].radius; // prevent sticking

              //Trigger bend and vibration
              platform.bendOffset = 5;
              platform.vibrationTimer = 20; // frames
              
              //Play sounds
              Mix_PlayChannel(-1, soundHitPlatform, 0);

              //add score
              score++;
        }
      }

      if (platform.vibrationTimer > 0) {
          platform.vibrationTimer--;

          // Vibrate left and right
          platform.x += (platform.vibrationTimer % 2 == 0) ? -2 : 2;

          // Reduce bend gradually
          if (platform.bendOffset > 0) {
              platform.bendOffset--;
          }
      }

      // collision - between balls
      for (int i = 0; i < NUM_BALLS; i++) {
          for (int j = i + 1; j < NUM_BALLS; j++) {
              int dx = balls[i].x - balls[j].x;
              int dy = balls[i].y - balls[j].y;
              int distanceSq = dx * dx + dy * dy;
              int radiusSum = balls[i].radius + balls[j].radius;

              if (distanceSq <= radiusSum * radiusSum) {
                  // Simple velocity swap
                  int tempVx = balls[i].vx;
                  int tempVy = balls[i].vy;
                  balls[i].vx = balls[j].vx;
                  balls[i].vy = balls[j].vy;
                  balls[j].vx = tempVx;
                  balls[j].vy = tempVy;
              }
          }
      }
    }

    // Set background color (R,G,B,A)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw all balls
    for (int i = 0; i < NUM_BALLS; i++) {
        //big circle
        SDL_SetRenderDrawColor(renderer, balls[i].r, balls[i].g, balls[i].b, 255);
        SDL_RenderFillCircle(renderer, balls[i].x, balls[i].y, balls[i].radius);

        //small circle
        SDL_SetRenderDrawColor(renderer, balls[i].r-100, balls[i].g-100, balls[i].b-100, 200);
        SDL_RenderFillCircle(renderer, balls[i].x - balls[i].radius/3, balls[i].y - balls[i].radius/3, balls[i].radius/4);
    }

    // draw platform
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Cyan
    // Simulate bend
    SDL_Rect rect = {
        platform.x,
        platform.y + platform.bendOffset,
        platform.width,
        platform.height - platform.bendOffset
    };
    SDL_RenderFillRect(renderer, &rect);

    // Draw score (top left)
    SDL_Color white = {255, 255, 255};
    char scoreText[32];
    sprintf(scoreText, "Score: %d", score);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText, white);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    // Draw high score (below score)
    char highScoreText[32];
    sprintf(highScoreText, "High: %d", highScore);
    SDL_Surface *highScoreSurface = TTF_RenderText_Solid(font, highScoreText, white);
    SDL_Texture *highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
    SDL_Rect highScoreRect = {10, 40, highScoreSurface->w, highScoreSurface->h};
    SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);
    SDL_FreeSurface(highScoreSurface);
    SDL_DestroyTexture(highScoreTexture);

    // Draw lives (hearts) on top right
    for (int i = 0; i < lives; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
        //SDL_RenderFillCircle(renderer, winWidth - 30 - i*35, 25, 15); // Adjust spacing as needed
        SDL_RenderFillHeart(renderer, winWidth - 30 - i*35, 25, 30); // Adjust size and spacing as needed
    }

    // Draw game start message
    if (gameState == STATE_START) {
        SDL_Color white = {255, 255, 255};

        SDL_Surface *goSurface1 = TTF_RenderText_Solid(font, "GnuSquash 1.0", white);
        SDL_Texture *goTexture1 = SDL_CreateTextureFromSurface(renderer, goSurface1);
        // rectangle (on the screen) to draw to - dstRect
        SDL_Rect goRect1 = {winWidth/2 - goSurface1->w/2, winHeight/2 - goSurface1->h*2, goSurface1->w, goSurface1->h};
        // SDL_RenderCopy(renderer, texture, srcRect, dstRect); NULL means copy whole texture
        SDL_RenderCopy(renderer, goTexture1, NULL, &goRect1);
        SDL_FreeSurface(goSurface1);
        SDL_DestroyTexture(goTexture1);

        SDL_Surface *goSurface2 = TTF_RenderText_Solid(font, "Press Enter to Start", white);
        SDL_Texture *goTexture2 = SDL_CreateTextureFromSurface(renderer, goSurface2);
        // rectangle (on the screen) to draw to - dstRect
        SDL_Rect goRect2 = {winWidth/2 - goSurface2->w/2, winHeight/2 - goSurface2->h/2, goSurface2->w, goSurface2->h};
        // SDL_RenderCopy(renderer, texture, srcRect, dstRect); NULL means copy whole texture
        SDL_RenderCopy(renderer, goTexture2, NULL, &goRect2);
        SDL_FreeSurface(goSurface2);
        SDL_DestroyTexture(goTexture2);
    }

    // Draw game over message
    if (gameState == STATE_GAMEOVER) {
        SDL_Color white = {255, 255, 255};
        SDL_Surface *goSurface3 = TTF_RenderText_Solid(font, "GAME OVER", white);
        SDL_Texture *goTexture3 = SDL_CreateTextureFromSurface(renderer, goSurface3);
        SDL_Rect goRect3 = {winWidth/2 - goSurface3->w/2, winHeight/2 - goSurface3->h*2, goSurface3->w, goSurface3->h};
        SDL_RenderCopy(renderer, goTexture3, NULL, &goRect3);
        SDL_FreeSurface(goSurface3);
        SDL_DestroyTexture(goTexture3);

        SDL_Surface *goSurface4 = TTF_RenderText_Solid(font, "Press Enter to Restart", white);
        SDL_Texture *goTexture4 = SDL_CreateTextureFromSurface(renderer, goSurface4);
        // rectangle (on the screen) to draw to - dstRect
        SDL_Rect goRect4 = {winWidth/2 - goSurface4->w/2, winHeight/2 - goSurface4->h/2, goSurface4->w, goSurface4->h};
        // SDL_RenderCopy(renderer, texture, srcRect, dstRect); NULL means copy whole texture
        SDL_RenderCopy(renderer, goTexture4, NULL, &goRect4);
        SDL_FreeSurface(goSurface4);
        SDL_DestroyTexture(goTexture4);
    }

    // Show what we've drawn
    SDL_RenderPresent(renderer);
  
    // Delay to control frame rate (16ms ~ 60 FPS)
    SDL_Delay(16);
  }

  // clean up audio
  Mix_FreeChunk(soundHitPlatform);
  Mix_FreeChunk(soundHitBottom);
  Mix_CloseAudio();

  // Clean uo
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  TTF_CloseFont(font);
  TTF_Quit();

  return 0;
}

