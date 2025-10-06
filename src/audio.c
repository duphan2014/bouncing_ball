#include "audio.h"
#include <stdio.h>

int audio_init(void) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    return 0;
}

void audio_cleanup(void) {
    Mix_CloseAudio();
}

Mix_Chunk* audio_load_sound(const char *filename) {
    Mix_Chunk *sound = Mix_LoadWAV(filename);
    if (!sound) {
        printf("Failed to load sound effect %s! SDL_mixer Error: %s\n", filename, Mix_GetError());
    }
    return sound;
}

void audio_play_sound(Mix_Chunk *sound) {
    if (sound) {
        Mix_PlayChannel(-1, sound, 0);
    }
}

void audio_free_sound(Mix_Chunk *sound) {
    if (sound) {
        Mix_FreeChunk(sound);
    }
}