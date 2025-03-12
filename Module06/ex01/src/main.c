#include "prog.h"
#include "i2c.h"
#include <util/delay.h>
#include <util/twi.h>

int main(void)
{
	uart_init(); // Init UART
	i2c_init();

	i2c_start();
	_delay_ms(40);
	i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
	i2c_write(0xBE); // initialization cmd
	i2c_write(0x08); // initialization cmd
	i2c_write(0x00); // initialization cmd
	_delay_ms(20);
	while (1)
	{
		i2c_start();
		i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
		i2c_write(0xAC); // measurement cmd
		i2c_write(0x33); // Temperature
		i2c_write(0x00); // humidity

		i2c_start();
		_delay_ms(100); // (see datasheet p.8 section 5.3.3) (80ms)
		i2c_write(AH20_ADDRESS << 1 | TW_READ);
		for (uint8_t i = 0; i < 6; ++i)
			uart_print_status(i2c_read(1));
		uart_print_status(i2c_read(0));
		uart_tx_string("\r\n");
//		i2c_stop();
		_delay_ms(2000); // (p.5)
	}
}

