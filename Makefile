# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Libraries to link
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image

# Output program name
TARGET = gnuash

# Source files
SRCS = src/audio.c src/ball.c src/game.c src/input.c src/main.c src/platform.c src/renderer.c src/ui.c src/sprite.c src/scene.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    SDL_CFLAGS := 
    SDL_LIBS := $(LIBS)
else ifeq ($(UNAME_S),Darwin)
    #SDL_CFLAGS := $(shell sdl2-config --cflags)
    #SDL_LIBS := $(shell sdl2-config --libs)
	SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_mixer SDL2_image)
    SDL_LIBS := $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_mixer SDL2_image)
endif

# Default rule
all: $(TARGET)

# compile .c to .o
# -I where to look for header file
%.o: %.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@ -I src

print-vars:
	echo "UNAME_S = $(UNAME_S)"
	echo "SDL_CFLAGS = $(SDL_CFLAGS)"
	echo "SDL_LIBS = $(SDL_LIBS)"

# lnk object files to build the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)  $(SDL_LIBS)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
