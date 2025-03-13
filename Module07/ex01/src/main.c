#include "james.h"
#include "prog.h"

int main(void)
{
    uart_init();
    uart_tx_string("EEPROM Sniper Mode\r\n");
    while (1)
	{
        uart_tx_string("\r\n\tType an address (hex) : ");
        uint16_t addr = uart_rx_hex();
        if (addr >= EEPROM_SIZE)
		{
            uart_tx_string("invalid address !\r\n");
            continue;
        }
        
        uart_tx_string("\r\n\tType a value (hex) : ");
        uint8_t value = uart_rx_hex();
        
        if (james_read_byte((uint8_t *)addr) != value)
		{
            james_write_byte((uint8_t *)addr, value);
			uart_tx_string("\r\n");
			print_hexdump(addr);
        }
    }
    return 0;
}
