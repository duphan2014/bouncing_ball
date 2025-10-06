#if defined(__APPLE__)
#include <SDL.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#else
#error "Unsupported platform"
#endif

#include "audio.h"
#include "input.h"

int main(){
    if(audio_init()!=0) {
        return 1;
    }

    Mix_Chunk *sound = audio_load_sound("sounds/boing_x.wav");
    if(!sound) {
        return 1;
    }
    audio_play_sound(sound);

    SDL_Delay(2000);

    audio_free_sound(sound);
    audio_cleanup();

    SDL_Event event;
    while(1) {
        input_handle_event(&event);
    }

    return 0;
}