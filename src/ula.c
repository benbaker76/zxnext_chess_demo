#include <stdlib.h>
#include "ula.h"
#include "bank.h"
#include "font.h"
#include "globals.h"

void ula_draw_text(uint8_t y, uint8_t x, const char *text)
{
	bank_set_16k(MMU_FONT, PAGE_FONT);

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

		ula_draw_char(ch, (y << 8) | x);
		
		x++;
		str++;
	}
}
