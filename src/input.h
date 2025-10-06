#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "game.h"

// Function declarations
void input_handle_events(struct Game *game, SDL_Event *event);
void input_handle_keyboard(struct Game *game, const Uint8 *keystate);

#endif // INPUT_H