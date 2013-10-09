#ifndef DEFS_HPP_INCLUDED
#define DEFS_HPP_INCLUDED

/// Compiling

// Choose the #define for your OS
#define OS_WINDOWS
//#define OS_UNIX

// Whether to print out detailed debugging information
//#define DEBUG_VERBOSE

/// General

// Configuration file
#define CONFIG_FILENAME "config.txt"

// How many milliseconds to sleep for each update, to avoid ravaging the CPU
#define SLEEP_MILLISECONDS 20

// How many seconds to wait before allowing to move again
#define MOVEMENT_DELAY 0.15

/// Drawing

// When multiple objects are in the same location, this controls how many
// seconds each object is draw before switching to the next
#define SECONDS_PER_OBJECT 0.35

// Width and height of the screen
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 35

// Shader
#define SHADER_FRAG_MONITOR3 "resources/monitor3.frag"

/// Sprites

// Spritesheet info
#define SPRITESHEET_FILENAME "resources/tiles.png"
#define SPRITESHEET_COLS 16
#define SPRITESHEET_ROWS 16
#define SPRITESHEET_SPRITE_W 9
#define SPRITESHEET_SPRITE_H 16

/// Levels

// Range of the level
#define LEVEL_WIDTH_MIN 1
#define LEVEL_WIDTH_MAX 80
#define LEVEL_HEIGHT_MIN 1
#define LEVEL_HEIGHT_MAX 24

// Level files
#define LEVEL_DIR "levels/"
#define LEVEL_000 LEVEL_DIR "000.txt"

#endif // DEFS_HPP_INCLUDED
