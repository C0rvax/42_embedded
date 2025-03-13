#include "james.h"
#include "prog.h"

uint8_t james_read_byte(const uint8_t *addr)
{
    while (EECR & (1 << EEPE)); // Wait for completion of previous write
    EEAR = (uint16_t)addr; // Set up address register
    EECR |= (1 << EERE); // Start eeprom read by writing EERE
    return EEDR; // Return data from data register
}

void james_write_byte(uint8_t *addr, uint8_t value)
{
    while (EECR & (1 << EEPE)); // Wait for completion of previous write
    EEAR = (uint16_t)addr; // Set up address register
    EEDR = value; // Set up data register
    EECR |= (1 << EEMPE); // Write logical one to EEMPE
    EECR |= (1 << EEPE); // Start eeprom write by setting EEPE
}

void print_hexdump(uint16_t highlight_addr)
{
    for (uint16_t i = 0; i < EEPROM_SIZE; i += BYTES_LINE)
	{
        uart_tx_string("0000");
		uart_print_hex16(i);
        uart_tx_string(" ");
        for (uint8_t j = 0; j < BYTES_LINE; j++)
		{
            if (i + j < EEPROM_SIZE)
			{
                uint8_t val = james_read_byte((uint8_t *)(i + j));
                if (i + j == highlight_addr)
				{
                    uart_tx_string("\x1B[31m"); // Rouge
                    uart_print_hex8(val);
                    uart_tx_string("\x1B[0m"); // Reset couleur
                }
				else
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
