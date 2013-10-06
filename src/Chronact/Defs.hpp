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

#define SHADER_FRAG_FRACTAL  SHADER_DIR "fractal.frag"
#define SHADER_FRAG_FRACTAL2 SHADER_DIR "fractal2.frag" // Green fractal
#define SHADER_FRAG_COLOURS  SHADER_DIR "colours.frag"
#define SHADER_FRAG_VLAD     SHADER_DIR "vlad.frag"
#define SHADER_FRAG_VLAD2    SHADER_DIR "vlad2.frag"
#define SHADER_FRAG_REAKTOR  SHADER_DIR "reaktor.frag" // wavy retro blue text "iteration ii" w/ horizontal green lines background
#define SHADER_FRAG_REAKTOR2 SHADER_DIR "reaktor2.frag" // wavy retro blue text "Iteration II" w/o background
#define SHADER_FRAG_MONITOR  SHADER_DIR "monitor.frag" // horizontal green lines background
#define SHADER_FRAG_MONITOR2 SHADER_DIR "monitor2.frag" // green glow and scanlines (written by me!)
#define SHADER_FRAG_MONITOR3 SHADER_DIR "monitor3.frag" // combination of monitor2.frag and fractal2.frag, edited to work well

// Spritesheet info
#define SPRITESHEET_FILENAME "resources/tiles.png"
#define SPRITESHEET_COLS 16
#define SPRITESHEET_ROWS 16
#define SPRITESHEET_SPRITE_W 9
#define SPRITESHEET_SPRITE_H 16

#endif // DEFS_HPP_INCLUDED
