# Gnuash - Modular C Game Structure

This document explains the modular restructuring of the Gnuash game following C best practices.

## Project Structure

```
gnuash/
├── src/                    # Source code directory
│   ├── main.c             # Entry point and main function
│   ├── game.h/.c          # Core game logic and state management
│   ├── ball.h/.c          # Ball physics and collision detection
│   ├── platform.h/.c      # Platform behavior and input handling
│   ├── renderer.h/.c      # All rendering and graphics functions
│   ├── audio.h/.c         # Audio system and sound effects
│   ├── input.h/.c         # Keyboard and event handling
│   └── ui.h/.c            # User interface rendering
├── fonts/                 # Font assets
├── sounds/                # Audio assets
├── Makefile.modular       # Updated Makefile for modular build
├── Makefile              # Original Makefile (for reference)
├── gnuash.c              # Original monolithic source (for reference)
└── README_MODULAR.md     # This file
```

## Module Responsibilities

### 1. **main.c**
- Program entry point
- Game initialization and cleanup
- Main game loop coordination

### 2. **game.h/.c** 
- Game state management (START, PLAYING, GAMEOVER)
- Core game context and data structures
- High-level game logic coordination
- High score management

### 3. **ball.h/.c**
- Ball physics and movement
- Wall collision detection
- Ball-to-ball collision detection
- Ball initialization and updates

### 4. **platform.h/.c**
- Platform movement and positioning
- Platform collision effects (bending, vibration)
- Input handling for platform control
- Platform boundary constraints

### 5. **renderer.h/.c**
- All drawing and rendering functions
- Circle and heart shape rendering
- Ball and platform rendering
- Graphics utilities

### 6. **audio.h/.c**
- Audio system initialization
- Sound loading and management
- Audio playback functions
- Resource cleanup

### 7. **input.h/.c**
- Event polling and handling
- Keyboard state management
- Fullscreen toggle logic
- Game state transitions from input

### 8. **ui.h/.c**
- Score and high score display
- Lives (hearts) rendering
- Start screen and game over screens
- Text rendering utilities

## Benefits of This Modular Structure

### 1. **Separation of Concerns**
- Each module has a single, well-defined responsibility
- Easier to understand and maintain individual components
- Changes in one module don't affect others unnecessarily

### 2. **Improved Maintainability**
- Bugs can be isolated to specific modules
- Features can be added/modified in focused areas
- Code reviews become more targeted and effective

### 3. **Better Testing**
- Individual modules can be unit tested
- Mock objects can replace dependencies
- Integration testing becomes more systematic

### 4. **Code Reusability**
- Modules can be reused in other projects
- Common functionality (renderer, audio) can be shared
- Easier to extract libraries from modules

### 5. **Team Development**
- Multiple developers can work on different modules
- Clearer interfaces reduce merge conflicts
- Easier to assign ownership of specific components

### 6. **Scalability**
- New features can be added as new modules
- Existing modules can be extended without affecting others
- Plugin architecture becomes possible

## Building the Modular Version

Use the new Makefile:

```bash
# Build the modular version
make -f Makefile.modular

# Clean build files
make -f Makefile.modular clean

# View build variables
make -f Makefile.modular print-vars
```

## Migration Strategy

If you want to gradually migrate from the monolithic version:

1. **Phase 1**: Extract utility functions (renderer, audio)
2. **Phase 2**: Separate data structures and their operations (ball, platform)
3. **Phase 3**: Extract UI and input handling
4. **Phase 4**: Centralize game state management

## Header Guard Best Practices

All header files use include guards to prevent multiple inclusion:
```c
#ifndef MODULE_H
#define MODULE_H
// ... content ...
#endif // MODULE_H
```

## Forward Declarations

Where needed, forward declarations are used to avoid circular dependencies:
```c
struct Game;  // Forward declaration in input.h
```

## Error Handling

Each module includes appropriate error checking and returns meaningful error codes where applicable.

## Future Improvements

1. **Configuration System**: Add a config module for game settings
2. **Entity System**: Implement a more sophisticated entity-component system
3. **Asset Management**: Create a dedicated asset loading system
4. **Physics Engine**: Extract physics into a separate, more robust module
5. **State Machine**: Implement a more sophisticated state management system

This modular structure provides a solid foundation for continued development and maintenance of the Gnuash game.