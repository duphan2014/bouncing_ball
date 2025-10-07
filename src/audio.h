#ifndef AUDIO_H
#define AUDIO_H

#if defined(__APPLE__)
#include <SDL_mixer.h>
#elif defined(__linux__)
#include <SDL2/SDL_mixer.h>
#else
#error "Unsupported platform"
#endif

int audio_init(void);
void audio_cleanup(void);
Mix_Chunk* audio_load_sound(const char* filename);
void audio_play_sound(Mix_Chunk* sound);
void audio_free_sound(Mix_Chunk* sound);

#endif // AUDIO_H