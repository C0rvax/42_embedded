#include "prog.h"
#include "i2c.h"
#include <util/twi.h>

int main(void)
{
	uart_init(); // Init UART
	i2c_init();

	uint8_t i = 0;
	while (i < 5)
	{
		i2c_start();
		i2c_write_status("I2c Start status : ");
		uart_tx_string(", ");
		i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
		i2c_write_status("I2c Write addr status : ");
		uart_tx_string("\r\n");
		i++;
	}
}

