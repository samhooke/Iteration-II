#ifndef TILES_HPP_INCLUDED
#define TILES_HPP_INCLUDED

// 0 -> 15
#define TILE_BLANK 0
#define TILE_FACE_OUTLINE 1
#define TILE_FACE_SOLID 2
#define TILE_HEART 3
#define TILE_DIAMOND 4
#define TILE_CLUB 5
#define TILE_SPADE 6
#define TILE_DOT_SOLID 7
#define TILE_DOT_SOLID_INVERT 8
#define TILE_DOT_OUTLINE 9
#define TILE_DOT_OUTLINE_INVERT 10
#define TILE_GENDER_MALE 11
#define TILE_GENDER_FEMALE_12
#define TILE_NOTE_HALF 13
#define TILE_NOTE_FULL 14
#define TILE_SUN 15

// 16 -> 31
#define TILE_SLOPE_RIGHT 16
#define TILE_SLOPE_LEFT 17
#define TILE_ARROW_UPDOWN 18
#define TILE_EXCLAMATION_DOUBLE 19
#define TILE_PILCROW 20
#define TILE_SECTION 21
#define TILE_RECTANGLE 22
#define TILE_ARROW_UPDOWNSTOP 23
#define TILE_ARROW_UP 24
#define TILE_ARROW_DOWN 25
#define TILE_ARROW_RIGHT 26
#define TILE_ARROW_LEFT 27
#define TILE_RIGHTANGLE 28
#define TILE_ARROW_LEFTRIGHT 29
#define TILE_SLOPE_UP 30
#define TILE_SLOPE_DOWN 31

// 32 -> 47
#define TILE_SPACE 32
#define TILE_EXCLAMATION 33
#define TILE_QUOTE 34
#define TILE_HASH 35
#define TILE_DOLLAR 36
#define TILE_PERCENT 37
#define TILE_AMPERSAND 38
#define TILE_APOSTROPHE 39
#define TILE_PARENTHESIS_OPEN 40
#define TILE_PARENTHESIS_CLOSE 41
#define TILE_ASTERISK 42
#define TILE_PLUS 43
#define TILE_COMMA 44
#define TILE_MINUS 45
#define TILE_FULLSTOP 46
#define TILE_SLASH_FORWARD 47

// 48 -> 63
#define TILE_0 48
#define TILE_1 49
#define TILE_2 50
#define TILE_3 51
#define TILE_4 52
#define TILE_5 53
#define TILE_6 54
#define TILE_7 55
#define TILE_8 56
#define TILE_9 57
#define TILE_COLON 58
#define TILE_SEMICOLON 59
#define TILE_CHEVRON_LEFT 60
#define TILE_EQUALS 61
#define TILE_CHEVRON_RIGHT 62
#define TILE_QUESTION 63

// 64 -> 79
#define TILE_AT 64
#define TILE_A_UPPER 65
#define TILE_B_UPPER 66
#define TILE_C_UPPER 67
#define TILE_D_UPPER 68
#define TILE_E_UPPER 69
#define TILE_F_UPPER 70
#define TILE_G_UPPER 71
#define TILE_H_UPPER 72
#define TILE_I_UPPER 73
#define TILE_J_UPPER 74
#define TILE_K_UPPER 75
#define TILE_L_UPPER 76
#define TILE_M_UPPER 77
#define TILE_N_UPPER 78
#define TILE_O_UPPER 79

// 80 -> 95
#define TILE_P_UPPER 80
#define TILE_Q_UPPER 81
#define TILE_R_UPPER 82
#define TILE_S_UPPER 83
#define TILE_T_UPPER 84
#define TILE_U_UPPER 85
#define TILE_V_UPPER 86
#define TILE_W_UPPER 87
#define TILE_X_UPPER 88
#define TILE_Y_UPPER 89
#define TILE_Z_UPPER 90
#define TILE_BRACKET_OPEN 91
#define TILE_SLASH_BACKWARD 92
#define TILE_BRACKET_CLOSE 93
#define TILE_CARET 94
#define TILE_UNDERSCORE 95

// 96 -> 111
#define TILE_GRAVEACCENT 96
#define TILE_A_LOWER 97
#define TILE_B_LOWER 98
#define TILE_C_LOWER 99
#define TILE_D_LOWER 100
#define TILE_E_LOWER 101
#define TILE_F_LOWER 102
#define TILE_G_LOWER 103
#define TILE_H_LOWER 104
#define TILE_I_LOWER 105
#define TILE_J_LOWER 106
#define TILE_K_LOWER 107
#define TILE_L_LOWER 108
#define TILE_M_LOWER 109
#define TILE_N_LOWER 110
#define TILE_O_LOWER 111

// 112 -> 127
#define TILE_P_LOWER 112
#define TILE_Q_LOWER 113
#define TILE_R_LOWER 114
#define TILE_S_LOWER 115
#define TILE_T_LOWER 116
#define TILE_U_LOWER 117
#define TILE_V_LOWER 118
#define TILE_W_LOWER 119
#define TILE_X_LOWER 120
#define TILE_Y_LOWER 121
#define TILE_Z_LOWER 122
#define TILE_BRACE_OPEN 123
#define TILE_VERTICALBAR_124
#define TILE_BRACE_CLOSE 125
#define TILE_TILDE 126
#define TILE_DEL 127

//...

// 176
#define TILE_FADE_LIGHT 176
#define TILE_FADE_MIDDLE 177
#define TILE_FADE_DARK 178

// Wall double
#define TILE_WD_NSW 185
#define TILE_WD_NS 186
#define TILE_WD_SW 187
#define TILE_WD_NW 188
#define TILE_WD_NE 200
#define TILE_WD_ES 201
#define TILE_WD_NEW 202
#define TILE_WD_ESW 203
#define TILE_WD_NES 204
#define TILE_WD_EW 205
#define TILE_WD_NESW 206
// There are no wall double tiles for single connections, so use an O for a pillar instead
#define TILE_WD_PILLAR TILE_O_UPPER
#define TILE_WD_N TILE_WD_PILLAR
#define TILE_WD_S TILE_WD_PILLAR
#define TILE_WD_E TILE_WD_PILLAR
#define TILE_WD_W TILE_WD_PILLAR

#endif // TILES_HPP_INCLUDED
