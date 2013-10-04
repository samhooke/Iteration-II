#ifndef DEFS_HPP_INCLUDED
#define DEFS_HPP_INCLUDED

// Choose the #define for your OS
#define OS_WINDOWS
//#define OS_UNIX

// How many milliseconds to sleep for each update, to avoid ravaging the CPU
#define SLEEP_MILLISECONDS 10

// Width and height of the screen
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 35

// Shaders
#define SHADER_DIR "resources/shaders/"
#define SHADER_FRAG_BLINK    SHADER_DIR "blink.frag"
#define SHADER_FRAG_BLUR     SHADER_DIR "blur.frag"
#define SHADER_FRAG_EDGE     SHADER_DIR "edge.frag"
#define SHADER_FRAG_PIXELATE SHADER_DIR "pixelate.frag"
#define SHADER_VERT_STORM    SHADER_DIR "storm.vert"
#define SHADER_VERT_WAVE     SHADER_DIR "wave.vert"

// Spritesheet info
#define SPRITESHEET_FILENAME "resources/tiles.png"
#define SPRITESHEET_COLS 16
#define SPRITESHEET_ROWS 16
#define SPRITESHEET_SPRITE_W 9
#define SPRITESHEET_SPRITE_H 16

#endif // DEFS_HPP_INCLUDED
