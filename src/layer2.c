#include "layer2.h"
#include <arch/zxn.h>
#include <intrinsic.h>
#include <z80.h>
#include <string.h>
#include "font.h"
#include "bank.h"
#include "globals.h"
#include "dma.h"

void layer2_draw_char(uint16_t x, uint16_t y, char ch, uint8_t color)
{
	bank_set_16k(MMU_FONT, PAGE_FONT);
	
	uint8_t lines = 8;
	uint8_t *font_address = font_spr + ((ch - 32) << 3);
	uint8_t screen_page = ZXN_READ_REG(REG_LAYER_2_RAM_PAGE);
	uint8_t *screen_address = (uint8_t *)zxn_addr_from_mmu(MMU_LAYER2);
	
	if ((x >= SCREEN_X) || (y >= SCREEN_Y))
	{
		return;
	}

#if (SCREEN_RES == RES_256x192)
	screen_address += x + (y % 64) * SCREEN_X;
	bank_set_16k(MMU_LAYER2, screen_page + (y >> 6));
#elif (SCREEN_RES == RES_320x256)
	screen_address += y + (x % 64) * SCREEN_Y;
	bank_set_16k(MMU_LAYER2, screen_page + (x >> 6));
#endif

	while (lines--)
	{
		uint8_t i;
		for (i = 0; i < 8; i++)
		{
			uint8_t bit = *font_address & (0x80 >> i);
			z80_bpoke(screen_address + i * SCREEN_Y, bit != 0 ? color : 0x00);
		}

#if (SCREEN_RES == RES_256x192)
		screen_address += SCREEN_X;
#elif (SCREEN_RES == RES_320x256)
		screen_address++;
#endif
		font_address++;
	}
}

void layer2_draw_text(uint8_t row, uint8_t column, const char *text, uint8_t color)
{
	uint16_t x = (column << 3);
	uint16_t y = (row << 3);
	char *str = (char *) text;

	if (text == NULL)
	{
		return;
	}

	while (*str != '\0')
	{
		char ch = *str;
		if ((ch < 32) || (ch > 127))
		{
			ch = '?';
		}

		layer2_draw_char(x, y, ch, color);
		
		x += 8;
		str++;
	}
}

void layer2_set_screen(char *p_image, uint8_t image_bank, uint8_t image_page)
{
	void *screen_address = (void *) zxn_addr_from_mmu(MMU_LAYER2);
	uint8_t screen_page = ZXN_READ_REG(REG_LAYER_2_RAM_PAGE);
	uint8_t old_page = bank_set_16k(image_bank, image_page);
	
#if (SCREEN_X == RES_256x192)
	for (uint8_t i = 0; i < 3; i++)
#else
	for (uint8_t i = 0; i < 5; i++)
#endif
	{
		bank_set_16k(image_bank, image_page + i);
		bank_set_16k(MMU_LAYER2, screen_page + i);
		memcpy(screen_address, (void *)p_image[i], BANKSIZE_16K);
	}

	bank_set_16k(image_bank, old_page);
}

void layer2_clear_screen(uint8_t value)
{
	void *screen_address = (void *)zxn_addr_from_mmu(MMU_LAYER2);
#if (SCREEN_RES == RES_256x192)
	for (uint8_t i = 0; i < 3; i++)
#else
	for (uint8_t i = 0; i < 5; i++)
#endif
	{
		bank_set_16k(MMU_LAYER2, PAGE_LAYER2 + i);
		dma_fill(screen_address, value, BANKSIZE_16K);
	}
}