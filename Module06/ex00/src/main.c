#include "prog.h"
#include "i2c.h"
#include <util/twi.h>

int main(void)
{
	uart_init(); // Init UART
	i2c_init();

	i2c_start();
	i2c_write_status("i2c Start status : ");
	uart_tx_string("\r\n");
	i2c_write(AH20_ADDRESS << 1 | TW_WRITE);
	i2c_write_status("i2c Write addr status : ");
	while (1);
}

