#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  const int winWidth = 640;
  const int winHeight = 480;

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

  // Square properties
  SDL_Rect rect = {200, 150, 50, 50}; // x, y, width, height
  int vx = 4; // orizontal speed
  int vy = 4; // vertical speed

  while (running) {
    // Handle events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

    // update square position
    rect.x += vx;
    rect.y += vy;

    // bounce off walls
    if (rect.x <= 0 || rect.x + rect.w >= winWidth) {
      vx = -vx;
    }

    if (rect.y <= 0 || rect.y + rect.h >= winHeight) {
      vy = -vy;
    }

    // Set background color (R,G,B,A)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw a red rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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

