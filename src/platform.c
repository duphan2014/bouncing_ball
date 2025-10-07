#include "platform.h"

void platform_init(Platform *platform, int winWidth, int winHeight) {
    platform->x = winWidth / 2 - 50;
    platform->y = winHeight - 30;
    platform->width = 100;
    platform->height = 15;
    platform->speed = 24;
    platform->bendOffset = 0;
    platform->vibrationTimer = 0;
}

void platform_update(Platform *platform, int winWidth) {
    if (platform->vibrationTimer > 0) {
        platform->vibrationTimer--;

        // Vibrate left and right
        platform->x += (platform->vibrationTimer %2 == 0 ) ? -2 : 2;

        // Reduce bend gradually
        if (platform->bendOffset > 0) {
            platform->bendOffset--;
        }
    }

    // Keep platform within window bounds
    if (platform->x <0) platform->x = 0;
    if (platform->x + platform->width > winWidth) platform->x = winWidth - platform->width;
}

void platform_handle_collision(Platform *platform) {
    // Trigger bend and vibration
    platform->bendOffset = 5;
    platform->vibrationTimer = 20; // frames
}

void platform_handle_input(Platform *platform, const Uint8 *keystate, int winWidth) {
    if (keystate[SDL_SCANCODE_LEFT]) {
        platform->x -= platform->speed;
    }

    if (keystate[SDL_SCANCODE_RIGHT]) {
        platform->x += platform->speed;
    }

    // keep platform within window bounds
    if (platform->x <0) platform->x = 0;
    if (platform->x + platform->width > winWidth) platform->x = winWidth - platform->width;
}