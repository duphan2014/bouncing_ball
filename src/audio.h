#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

// Function declarations
int audio_init(void);
void audio_cleanup(void);
Mix_Chunk* audio_load_sound(const char *filename);
void audio_play_sound(Mix_Chunk *sound);
void audio_free_sound(Mix_Chunk *sound);

#endif // AUDIO_H