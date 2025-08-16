#ifndef _GLOBALS_H
#define _GLOBALS_H

#define RTM_28MHZ				0x03

#define WFRAMES					4

#define MMU_LAYER2				MMU_4000
#define PAGE_LAYER2				8

#define MMU_CHESSBOARD			MMU_0000
#define PAGE_CHESSBOARD			20

#define MMU_CHESSMEN			MMU_0000
#define PAGE_CHESSMEN			25

#define MMU_FONT				MMU_0000
#define PAGE_FONT				25

#define TILE_X					8
#define TILE_Y					8

#define RES_256x192				0
#define RES_320x256				1
#define RES_640x256				2

#define SCREEN_RES				RES_320x256

#if (SCREEN_RES == RES_256x192)
#define SCREEN_X				256
#define SCREEN_Y				192
#elif (SCREEN_RES == RES_320x256)
#define SCREEN_X				320
#define SCREEN_Y				256
#elif (SCREEN_RES == RES_640x256)
#define SCREEN_X				640
#define SCREEN_Y				256
#endif

#define SCREEN_SIZE				(SCREEN_X * SCREEN_Y)
#define SCREEN_TILES_X			(SCREEN_X / 8)
#define SCREEN_TILES_Y			(SCREEN_Y / 8)
#define SCREEN_TILES_COUNT		(SCREEN_TILES_X * SCREEN_TILES_Y)

#define FP 1 // Pawn
#define FN 2 // Knight
#define FB 3 // Bishop
#define FR 4 // Rook
#define FQ 5 // Queen
#define FK 6 // King

#define MIN(a, b)				(((a) < (b)) ? (a) : (b))
#define MAX(a, b)				(((a) > (b)) ? (a) : (b))
#define CLAMP(x, lower, upper)	(MIN(upper, MAX(x, lower)))
#define printAt(col, row, str)	printf("\x16%c%c%s", (col), (row), (str))

extern void breakpoint();

#endif
