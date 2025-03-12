#include <avr/io.h>
#include <avr/eeprom.h>
#include "prog.h"

#define EEPROM_SIZE 1024 // Modifier selon le microcontrôleur

void print_hexdump(void)
{
    for (uint16_t i = 0; i < EEPROM_SIZE; i += 16)
	{
        uart_tx_string("\r\n");
        uart_print_status((i >> 8) & 0xFF);
        uart_print_status(i & 0xFF);
        uart_tx_string("  ");
        for (uint8_t j = 0; j < 16; j++)
		{
            if (i + j < EEPROM_SIZE)
			{
                uint8_t val = eeprom_read_byte((uint8_t *)(i + j));
                uart_print_status(val);
            }
			else
                uart_tx_string("   ");
        }
    }
    uart_tx_string("\r\n");
}

int main(void) {
    uart_init();
    print_hexdump();
    while (1);
    return 0;
}

