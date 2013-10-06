#ifndef DEFS_HPP_INCLUDED
#define DEFS_HPP_INCLUDED

// Choose the #define for your OS
#define OS_WINDOWS
//#define OS_UNIX

// Configuration file
#define CONFIG_FILENAME "config.txt"

// How many milliseconds to sleep for each update, to avoid ravaging the CPU
#define SLEEP_MILLISECONDS 10

// Width and height of the screen
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 35

// Shader
#define SHADER_FRAG_MONITOR3 "resources/monitor3.frag"

// Spritesheet info
#define SPRITESHEET_FILENAME "resources/tiles.png"
#define SPRITESHEET_COLS 16
#define SPRITESHEET_ROWS 16
#define SPRITESHEET_SPRITE_W 9
#define SPRITESHEET_SPRITE_H 16

#endif // DEFS_HPP_INCLUDED
