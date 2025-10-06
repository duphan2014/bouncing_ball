#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL2/SDL.h>

typedef struct {
    int x, y;
    int width, height;
    int speed;
    int bendOffset;     // For bending effect
    int vibrationTimer; // For vibration duration
} Platform;

// Function declarations
void platform_init(Platform *platform, int winWidth, int winHeight);
void platform_update(Platform *platform, int winWidth);
void platform_handle_collision(Platform *platform);
void platform_handle_input(Platform *platform, const Uint8 *keystate, int winWidth);

#endif // PLATFORM_H