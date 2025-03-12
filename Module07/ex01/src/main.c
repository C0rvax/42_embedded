#include <avr/io.h>
#include <avr/eeprom.h>
#include "prog.h"

#define EEPROM_SIZE 1024

void print_hexdump(uint16_t highlight_addr)
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
                if (i + j == highlight_addr)
				{
                    uart_tx_string("\x1B[31m"); // Rouge
                    uart_print_status(val);
                    uart_tx_string("\x1B[0m"); // Reset couleur
                }
				else
                    uart_print_status(val);
			}
            else
                uart_tx_string("   ");
        }
    }
    uart_tx_string("\r\n");
}

int main(void)
{
    uart_init();
    uart_tx_string("EEPROM Sniper Mode\r\n");
    while (1)
	{
        uart_tx_string("\r\n\tEntrez une adresse (hex) : ");
        uint16_t addr = uart_rx_hex();
        if (addr >= EEPROM_SIZE)
		{
            uart_tx_string("Adresse invalide !\r\n");
            continue;
        }
        
        uart_tx_string("Entrez une valeur (hex) : ");
        uint8_t value = uart_rx_hex();
        
        if (eeprom_read_byte((uint8_t *)addr) != value)
		{
            eeprom_write_byte((uint8_t *)addr, value);
			print_hexdump(addr);
        }
    }
    return 0;
}

