#if defined(__APPLE__)
#include <SDL.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#else
#error "Unsupported platform"
#endif

#include <stdio.h>

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
} Platform;

#define NUM_BALLS 5
Ball balls[NUM_BALLS] = {
    {100, 100, 3, 2, 20, 250, 0, 0},
    {200, 150, -2, 3, 20, 250, 0, 0},
    {300, 200, 4, -3, 20, 0, 250, 0},
    {400, 250, -3, -2, 20, 0, 250, 0},
    {500, 300, 2, 4, 20, 0, 0 , 250}
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

int main(int argc, char* argv[]) {
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  const int winWidth = 1024; //640;
  const int winHeight = 768; //480;

  // initialize platform
  Platform platform = { winWidth / 2 - 50, winHeight - 30, 100, 15, 16 };

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
    // Handle events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

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

    // Wall collision
    for (int i = 0; i < NUM_BALLS; i++){
      balls[i].x += balls[i].vx;
      balls[i].y += balls[i].vy;

      // Wall collision - can bounce off side walls and top
      if (balls[i].x - balls[i].radius <= 0 || balls[i].x + balls[i].radius >= winWidth) {
          balls[i].vx = -balls[i].vx;
      }

      if (balls[i].y - balls[i].radius <= 0 || balls[i].y + balls[i].radius >= winHeight) {
          balls[i].vy = -balls[i].vy;
      }

      // Platform collision
      if (balls[i].y + balls[i].radius >= platform.y &&
          balls[i].x >= platform.x &&
          balls[i].x <= platform.x + platform.width &&
          balls[i].y + balls[i].radius <= platform.y + platform.height) {
            balls[i].vy = -balls[i].vy;
            balls[i].y = platform.y - balls[i].radius; // prevent sticking
      }
    }

    // Balls collision
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
    SDL_Rect rect = { platform.x, platform.y, platform.width, platform.height };
    SDL_RenderFillRect(renderer, &rect);


    // Show what we've drawn
    SDL_RenderPresent(renderer);
  
    // Delay to control frame rate (16ms ~ 60 FPS)
    SDL_Delay(16);
  }

  // Clean uo
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

