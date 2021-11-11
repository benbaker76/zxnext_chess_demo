#ifndef _ULA_H
#define _ULA_H

#include <stdint.h>
#include <stdbool.h>

#define REG_ULA_CONTROL  0x68

extern void ula_draw_text(uint8_t y, uint8_t x, const char *text);
extern void ula_draw_char(uint8_t ch, uint16_t yx);
extern void ula_draw_dec(uint16_t value, uint16_t yx);
extern void ula_draw_hex(uint16_t value, uint16_t yx);

#endif
