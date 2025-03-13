#include "james.h"
#include "prog.h"

void print_hexdump(void)
{
    for (uint16_t i = 0; i < EEPROM_SIZE; i += BYTES_LINE)
	{
//        uart_tx_string("\r\n");
		uart_print_hex16(i);
        uart_tx_string("  ");
        for (uint8_t j = 0; j < BYTES_LINE; j++)
		{
            if (i + j < EEPROM_SIZE)
			{
                uint8_t val = eeprom_read_byte((uint8_t *)(i + j));
                uart_print_hex8(val);
				if (j % 2)
					uart_tx(' ');
            }
			else
                uart_tx_string("   ");
        }
		uart_tx_string("\r\n");
    }
}
