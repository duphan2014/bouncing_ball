# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Libraries to link
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_ttf

# Output program name
TARGET = gnuash

# Source files
SRCS = gnuash.c

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
	SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_mixer)
    SDL_LIBS := $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_mixer)
endif

# Default rule
all: $(TARGET)

# compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

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
