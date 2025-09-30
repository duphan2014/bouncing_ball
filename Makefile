# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Libraries to link
LIBS = -lSDL2

# Output program name
TARGET = bouncing_ball

# Source files
SRCS = bouncing_ball.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# How to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
