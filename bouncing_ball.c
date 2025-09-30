#include <SDL2/SDL.h>
#include <stdio.h>

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
  int cx = 200, cy = 150; // center
  int radius = 25;
  int vx = 1; // orizontal speed
  int vy = 1; // vertical speed

  while (running) {
    // Handle events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

    // update square position
    cx += vx;
    cy += vy;

    // bounce off walls
    if (cx - radius <= 0 || cx + radius >= winWidth) {
      vx = -vx;
    }

    if (cy - radius <= 0 || cy + radius >= winHeight) {
      vy = -vy;
    }

    // Set background color (R,G,B,A)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw a red rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillCircle(renderer, cx, cy, radius);

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

