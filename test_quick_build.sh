gcc -o gnuash src/audio.c src/ball.c src/game.c src/input.c src/main.c src/platform.c src/renderer.c src/ui.c $(pkg-config --cflags sdl2 SDL2_ttf SDL2_mixer) $(pkg-config --libs sdl2 SDL2_ttf SDL2_mixer) -I src

