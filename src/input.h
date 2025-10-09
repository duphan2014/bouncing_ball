#ifndef INPUT_H
#define INPUT_H

#if defined(__APPLE__)
#include <SDL.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#else
#error "Unsupported platform"
#endif
#include "game.h"
//#include "platform.h"

void input_handle_events(Game *game, SDL_Event *event);
void input_handle_keyboard(Game *game, const Uint8 *keystate);

#endif // INPUT_H