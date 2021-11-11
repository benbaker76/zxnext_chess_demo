/*******************************************************************************
 * Ben Baker 2020
 *
 * A relative sprite demo for Sinclair ZX Spectrum Next.
 ******************************************************************************/

#include <arch/zxn.h>
#include <arch/zxn/color.h>
#include <input.h>
#include <z80.h>
#include <intrinsic.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "font.h"
#include "chessmen.h"
#include "chessboard.h"
#include "globals.h"
#include "ula.h"
#include "layer2.h"
#include "bank.h"
#include "sprites.h"

#pragma output CRT_ORG_CODE = 0x8184
#pragma output REGISTER_SP = 0
#pragma output CLIB_MALLOC_HEAP_SIZE = 0
#pragma output CLIB_STDIO_HEAP_SIZE = 0
#pragma output CLIB_FOPEN_MAX = -1
#pragma output CRT_ORG_BANK_8 = 0x4000
#pragma output CRT_ORG_BANK_20 = 0x0000
#pragma output CRT_ORG_BANK_21 = 0x0000
#pragma output CRT_ORG_BANK_22 = 0x0000
#pragma output CRT_ORG_BANK_23 = 0x0000
#pragma output CRT_ORG_BANK_24 = 0x0000
#pragma output CRT_ORG_BANK_25 = 0x0000

/*
 * Define IDE_FRIENDLY in your C IDE to disable Z88DK C extensions and avoid
 * parser errors/warnings in the IDE. Do NOT define IDE_FRIENDLY when compiling
 * the code with Z88DK.
 */
#ifdef IDE_FRIENDLY
#define __z88dk_fastcall
#define __preserves_regs(...)
#endif

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

static void hardware_init(void);

static void isr_init(void);

static void background_init(void);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

static void hardware_init(void)
{
	// Make sure the Spectrum ROM is paged in initially.
	IO_7FFD = IO_7FFD_ROM0;

	// Put Z80 in 28 MHz turbo mode.
	ZXN_NEXTREG(REG_TURBO_MODE, RTM_28MHZ);

	// Disable RAM memory contention.
	ZXN_NEXTREGA(REG_PERIPHERAL_3, ZXN_READ_REG(REG_PERIPHERAL_3) | RP3_DISABLE_CONTENTION);

	ZXN_NEXTREG(REG_PALETTE_CONTROL, 0);
	ZXN_NEXTREG(REG_PALETTE_INDEX, 24);
	ZXN_NEXTREG(REG_PALETTE_VALUE_8, ZXN_RGB332_ZX_BRIGHT_MAGENTA);
	
	ZXN_NEXTREG(REG_GLOBAL_TRANSPARENCY_COLOR, ZXN_RGB332_ZX_BRIGHT_MAGENTA);
	ZXN_NEXTREG(REG_SPRITE_TRANSPARENCY_INDEX, 0);

	ZXN_NEXTREGA(REG_SPRITE_LAYER_SYSTEM, RSLS_LAYER_PRIORITY_USL | RSLS_SPRITES_OVER_BORDER | RSLS_SPRITES_VISIBLE);

	ZXN_NEXTREG(REG_LAYER_2_RAM_PAGE, PAGE_LAYER2);
	
	IO_LAYER_2_CONFIG = IL2C_SHOW_LAYER_2;

	ZXN_NEXTREG(REG_CLIP_WINDOW_LAYER_2, 1);
	ZXN_NEXTREG(REG_CLIP_WINDOW_LAYER_2, 254);
	ZXN_NEXTREG(REG_CLIP_WINDOW_LAYER_2, 1);
	ZXN_NEXTREG(REG_CLIP_WINDOW_LAYER_2, 254);
	
	ZXN_NEXTREG(REG_LAYER_2_OFFSET_X_H, 0);
	ZXN_NEXTREG(REG_LAYER_2_OFFSET_X, 0);
	ZXN_NEXTREG(REG_LAYER_2_OFFSET_Y, 0);
	
	ZXN_NEXTREG(REG_ULA_CONTROL, 0x80);

#if (SCREEN_RES == RES_256x192)
	ZXN_NEXTREG(REG_LAYER_2_CONTROL, LAYER_2_256x192x8);
#elif (SCREEN_RES == RES_320x256)
	ZXN_NEXTREG(REG_LAYER_2_CONTROL, LAYER_2_320x256x8);
#elif (SCREEN_RES == RES_640x256)
	ZXN_NEXTREG(REG_LAYER_2_CONTROL, LAYER_2_640x256x4);
#endif
}

static void isr_init(void)
{
	// Set up IM2 interrupt service routine:
	// Put Z80 in IM2 mode with a 257-byte interrupt vector table located
	// at 0x8000 (before CRT_ORG_CODE) filled with 0x81 bytes. Install an
	// empty interrupt service routine at the interrupt service routine
	// entry at address 0x8181.

	intrinsic_di();
	im2_init((void *) 0x8000);
	memset((void *) 0x8000, 0x81, 257);
	z80_bpoke(0x8181, 0xFB);
	z80_bpoke(0x8182, 0xED);
	z80_bpoke(0x8183, 0x4D);
	intrinsic_ei();
}

static void background_create(void)
{
	zx_border(INK_BLACK);
	zx_cls(INK_WHITE | PAPER_BLACK | BRIGHT);
}

int main(void)
{
	hardware_init();
	isr_init();
	background_create();
	layer2_clear_screen(0);
	sprites_clear();
	
	bank_set_16k(MMU_CHESSMEN, PAGE_CHESSMEN);
	
	sprites_create();
	
	sprite_set_display_palette(true);
	sprite_set_rw_palette(true);
	sprite_set_palette(chessmen_nxp, 16, 0);
	
	layer2_set_screen(chessboard_sequence, MMU_CHESSBOARD, PAGE_CHESSBOARD);
	
	layer2_draw_text(2, 31, "Hello", ZXN_RGB332_ZX_BRIGHT_WHITE);
	layer2_draw_text(3, 31, "World!", ZXN_RGB332_ZX_BRIGHT_WHITE);

	while (true)
	{
		if (in_inkey() != 0)
		{
			break;
		}

		// Wait for vertical blanking interval.
		intrinsic_halt();
	}

	// Trig a soft reset. The Next hardware registers and I/O ports will be reset by NextZXOS after a soft reset.
	ZXN_NEXTREG(REG_RESET, RR_SOFT_RESET);
	return 0;
}
