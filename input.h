#ifndef INPUT_H
#define INPUT_H

#if defined(__APPLE__)
#include <SDL.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#else
#error "Unsupported platform"
#endif

void input_handle_event(SDL_Event* event);

#endif